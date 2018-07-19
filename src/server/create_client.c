/*
** create_client.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Sun Jun 12 15:53:52 2016 Delaunay Marc
** Last update Sun Jun 26 20:41:37 2016 Louis Casamayou
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "client.h"

void		cli_del(void *s)
{
  t_client	*this;

  this = (t_client *)s;
  if (this->fd)
    close(this->fd);
  delete(this->precious);
  delete(this->timer);
  delete(this->life);
}

static void	t_client_assign(t_client_init var, t_client *new)
{
  new->lvl = 1;
  new->dir = rand() % 4;
  new->x = rand() % var.s->x;
  new->y = rand() % var.s->y;
  new->team = NULL;
  new->mask = 0;
  new->inv[nourriture] = 10;
}

t_client		*t_client_new(t_client_init var)
{
  t_client		*new;
  struct sockaddr_in    in_client;
  socklen_t		in_size;
  static size_t		id = 0;

  if (!var.s || !var.s->x || !var.s->y)
    return (NULL);
  if ((new = (t_client *)new(t_object, sizeof(t_client), &cli_del)) == NULL)
    return (NULL);
  in_size = sizeof(struct sockaddr_in);
  if ((new->fd = accept(var.s->fd,
			(struct sockaddr *)&in_client, &in_size)) == -1)
    return (NULL);
  if ((new->precious = new(t_circularBuff, 10)) == NULL)
    return (NULL);
  if ((new->timer = new(t_timer)) == NULL ||
      (new->life = new(t_timer, TTIME(LIFE_UNIT, var.s->time))) == NULL)
    return (NULL);
  new->id = id++;
  t_client_assign(var, new);
  return (new);
}

int		read_client(t_client *this)
{
  char		*str;
  int		r;

  if ((r = get_next_line(this, &str)) < 2)
    {
      if (r == 0)
	{
	  if (CBPUT(this->precious, str) != CBF_NOERR)
	    free(str);
	  return (0);
	}
      return (2);
    }
  if (r == 3)
    perror("malloc");
  else if (r == 4)
    perror("read");
  return (1);
}
