/*
** walk.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:10:40 2016 Delaunay Marc
** Last update Sun Jun 26 04:10:56 2016 Delaunay Marc
*/

#include "server.h"

int     walk_check(t_client *this, t_server *server, char *arg)
{
  int   val;

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_WALK)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&walk;
      return (1);
    }
  return (0);
}

int	walk(t_client *this, t_server *server, char *arg)
{
  t_field	*start;
  t_field	*end;

  if (walk_check(this, server, arg))
    return (0);
  start = V2DGETP(t_field*, server->field, this->y, this->x);
  map_remove(start->players, &this->fd);
  move(this);
  this->x = MOD(this->x, server->field->sx);
  this->y = MOD(this->y, server->field->sx);
  end = V2DGETP(t_field*, server->field, this->y, this->x);
  map_add(end->players, &this->fd, this);
  graphic_pos(this, server);
  write_iov(this, "ok\n");
  (void)arg;
  return (0);
}
