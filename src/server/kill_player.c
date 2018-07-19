/*
** kill_player.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Wed Jun 22 19:03:59 2016 Delaunay Marc
** Last update Sun Jun 26 23:33:25 2016 Loïc GIGOMAS
*/

#include "server.h"

int	kill_player(t_client *this, t_server *server)
{
  char	buffer[24];

  if (!timer_finished(this->life))
    return (0);
  if (this->inv[nourriture])
    {
      --this->inv[nourriture];
      add_timer(this->life, TTIME(LIFE_UNIT, server->time));
      return (0);
    }
  else
    {
      if (this->team && !(this->mask & from_egg))
	++this->team->maxConn;
      sprintf(buffer, "pdi %zu\n", this->id);
      write_graphic(server, buffer);
      write_iov(this, "mort\n");
      iov_send(this);
      if (this->team)
	map_remove(this->team->players, &this->fd);
      return (1);
    }
  return (0);
}
