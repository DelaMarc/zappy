/*
** select.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:21:31 2016 Delaunay Marc
** Last update Sun Jun 26 16:15:54 2016 Louis Casamayou
*/

#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "foreach.h"
#include "server.h"
#include "client.h"

static void	get_max_fd(t_server *s)
{
  t_client	*this;
  size_t	i;

  if (!s)
    return ;
  s->max_fd = s->fd;
  FOREACH(t_pair *, p, s->clients)
    if (*(int *)p->first > s->max_fd)
      s->max_fd = *(int *)p->first;
  for (i = 0; i < s->graphics->size; ++i)
    {
      this = list_get(s->graphics, i);
      if ((int)this->fd > s->max_fd)
	s->max_fd = this->fd;
    }
}

static int	add_client(t_server *server, fd_set *readfds)
{
  t_client	*n;

  if (FD_ISSET(server->fd, readfds))
    {
      if ((n = new(t_client, server)) == NULL)
	{
	  if (errno)
	    perror("client");
	  return (1);
	}
      if ((map_add(server->clients, &n->fd, n)) != MAP_NOERR)
	return (1);
      if ((map_add(V2DGETP(t_field *, server->field,
			   n->y, n->x)->players, &n->fd, n)) != MAP_NOERR)
	return (1);
      FD_SET(n->fd, &server->readfds);
      FD_SET(n->fd, &server->writefds);
      write_iov(n, "BIENVENUE\n");
    }
  return (0);
}

static int	check_fds(t_server *server, fd_set *readfds, fd_set *writefds)
{
  t_client	*tmp;

  if (add_client(server, readfds))
    return (1);
  if (server->clients->size)
    {
      FOREACH(t_pair *, p, server->clients)
	{
	  tmp = (t_client *)p->second;
	  if (FD_ISSET(tmp->fd, readfds))
	    {
	      if (read_client(tmp) == 1)
		return (remove_client(server, tmp));
	    }
	  else if (tmp->iovcnt &&
		   FD_ISSET(tmp->fd, writefds) &&
		   iov_send(tmp))
	    return (remove_client(server, tmp));
	}
    }
  return (check_fd_graphics(server, writefds, readfds));
}

int		check_cmd_loop(t_server *server)
{
  t_client	*this;
  int		r;

  manage_eggs(server);
  FOREACH(t_pair *, tmp, server->clients)
    {
      this = (t_client *)tmp->second;
      if ((r = check_cmd(server, this)))
	{
	  if (r == 2)
	    return (0);
	  remove_client(server, this);
	  return (r - 1);
	}
    }
  return (check_cmd_loop_graphics(server));
}

int			server_loop(t_server *server)
{
  struct timeval	tv;
  int			s;
  fd_set		readfds;
  fd_set		writefds;

  FD_ZERO(&server->readfds);
  FD_ZERO(&server->writefds);
  FD_SET(server->fd, &server->readfds);
  FD_SET(server->fd, &server->writefds);
  while (server->run == 1)
    {
      tv = (struct timeval){0, 0};
      readfds = server->readfds;
      writefds = server->writefds;
      refuel_eat(server);
      get_max_fd(server);
      if ((s = select(server->max_fd + 1,
		      &readfds, &writefds, NULL, &tv)) == -1)
	return (1);
      if ((s > 0 && check_fds(server, &readfds, &writefds))
	  || check_cmd_loop(server))
	return (1);
      usleep(1);
    }
  return (0);
}
