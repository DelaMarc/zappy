/*
** player_afk.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:20:47 2016 Delaunay Marc
** Last update Sun Jun 26 04:20:48 2016 Delaunay Marc
*/

#include "server.h"

int	player_afk(t_client *this, t_server *server, char *arg)
{
  write_iov(this, "ko\n");
  if (arg)
    free(arg);
  (void)server;
  return (0);
}
