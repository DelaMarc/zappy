/*
** select.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/client
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Tue Jun 21 15:58:57 2016 Delaunay Marc
** Last update Sun Jun 26 21:11:07 2016 Loïc GIGOMAS
*/

#include <unistd.h>
#include <stdio.h>
#include "client/ai.h"
#include "client/client.h"

int	check_client_fd(t_client *this, fd_set *readfds, fd_set *writefds)
{
  char	*data;
  int	gnl;

  data = NULL;
  if (FD_ISSET(this->fd, readfds) || this->last_gnl == 1)
    {
      gnl = get_next_line(this, (this->last_gnl == 1 ? -1 : this->fd), &data);
      if (gnl >= 3)
	return (1);
      this->last_gnl = gnl;
      if ((gnl == 0 || gnl == 1) && data != NULL)
	CBPUT(this->received, data);
    }
  else if (this->iovcnt && FD_ISSET(this->fd, writefds))
    {
      if (iov_send(this))
	return (1);
    }
  return (0);
}

static int	loop_markov(t_client *c)
{
  t_markov_node	*n;
  int		i;

  if ((i = markov_mandat(c->markov, c)) != 0)
    return (i);
  n = VGETP(t_markov_node *, c->markov->nodes, c->markov->actual);
  if (((t_state_f)n->data)(c) == MARKOV_FINISHED)
    {
      if ((n = markov_next(c->markov, c)) == NULL)
	{
	  fprintf(stderr, "ERROR : no next state defined N°%d\n",
		  c->markov->actual);
	  return (1);
	}
    }
  else
    return (0);
  ((t_state_f)n->data)(c);
  return (0);
}

int	client_loop(t_client *this)
{
  struct timeval	tv;
  int			s;
  fd_set		readfds;
  fd_set		writefds;

  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_SET(this->fd, &this->readfds);
  FD_SET(this->fd, &this->writefds);
  while (this->run == 1)
    {
      tv = (struct timeval){0, 0};
      readfds = this->readfds;
      writefds = this->writefds;
      if ((s = select(this->fd + 1,
		      &readfds, &writefds, NULL, &tv)) == -1)
	return (1);
      if (s > 0 && check_client_fd(this, &readfds, &writefds))
	return (1);
      if (loop_markov(this))
      	return (1);
      usleep(1000);
    }
  return (0);
}
