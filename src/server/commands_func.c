/*
** commands_func.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:18:00 2016 Delaunay Marc
** Last update Sun Jun 26 04:32:14 2016 Louis Casamayou
*/

#include "server.h"

int     commands_set_timer(t_client *this, t_server *server, int time)
{
  int	val;

  if ((val = timer_finished(this->timer)) == TIMER_RUN
      || val == TIMER_FUNC)
    return (0);
  else if (this->ptr_func == NULL)
    {
      if ((this->timer = new(t_timer, TTIME(time, server->time))) == NULL)
        return (0);
      return (1);
    }
  return (2);
}

void	move_player_to(t_server *s, t_client *c, int x, int y)
{
  map_remove(V2DGETP(t_field *, s->field, c->y, c->x)->players, &c->fd);
  c->x = x;
  c->y = y;
  map_add(V2DGETP(t_field *, s->field, c->y, c->x)->players, &c->fd, c);
}

void    move(t_client *this)
{
  this->x += ((this->dir + 1) & 1) * (1 - (this->dir & 2));
  this->y += (this->dir & 1) * (1 - (this->dir & 2));
}

void	graphic_end(t_server *server, char *team)
{
  char	buffer[512];

  server->run = 0;
  sprintf(buffer, "seg %s\n", team);
  write_graphic(server, buffer);
}
