/*
** right.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:21:10 2016 Delaunay Marc
** Last update Sun Jun 26 04:21:11 2016 Delaunay Marc
*/

#include "server.h"

int	right_check(t_client *this, t_server *server, char *arg)
{
  int	val;

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_RIGHT)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&right;
      return (1);
    }
  return (0);
}

int	right(t_client *this, t_server *server, char *arg)
{
  if (right_check(this, server, arg))
    return (0);
  this->dir = MOD((this->dir + 1), 4);
  write_iov(this, "ok\n");
  graphic_pos(this, server);
  return (0);
}
