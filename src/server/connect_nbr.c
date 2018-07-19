/*
** connect_nbr.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:18:12 2016 Delaunay Marc
** Last update Sun Jun 26 04:18:13 2016 Delaunay Marc
*/

#include "server.h"

int	connect_nbr_check(t_client *this, char *arg)
{
  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  return (0);
}

int		connect_nbr(t_client *this, t_server *server, char *arg)
{
  size_t	nb_slots;
  char		buffer[8];

  if (connect_nbr_check(this, arg))
    return (0);
  (void)server;
  nb_slots = this->team->maxConn;
  sprintf(buffer, "%zu\n", nb_slots);
  write_iov(this, buffer);
  return (0);
}
