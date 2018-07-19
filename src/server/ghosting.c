/*
** ghosting.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:11:43 2016 Delaunay Marc
** Last update Sun Jun 26 04:11:45 2016 Delaunay Marc
*/

#include "server.h"

int	delete_client(t_server *s, t_client *c)
{
  map_remove(s->clients, &c->fd);
  map_remove(V2DGETP(t_field *, s->field, c->y, c->x)->players, &c->fd);
  delete(c);
  return (0);
}

int	remove_client(t_server *s, t_client *c)
{
  char	*tmp;

  FD_CLR(c->fd, &s->readfds);
  FD_CLR(c->fd, &s->writefds);
  while ((tmp = CBGET(char *, c->precious)))
    free(tmp);
  map_remove(s->clients, &c->fd);
  map_remove(V2DGETP(t_field *, s->field, c->y, c->x)->players, &c->fd);
  delete(c);
  return (0);
}

int	ghosting_client(t_server *s, t_client *c)
{
  char	*tmp;

  FD_CLR(c->fd, &s->readfds);
  FD_CLR(c->fd, &s->writefds);
  while ((tmp = CBGET(char *, c->precious)))
    free(tmp);
  close(c->fd);
  c->mask = c->mask | ghost;
  free(c->cmd_arg);
  c->ptr_func = NULL;
  set_timer(c->timer, 0);
  return (0);
}
