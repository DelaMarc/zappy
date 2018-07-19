/*
** server2.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:21:26 2016 Delaunay Marc
** Last update Sun Jun 26 04:21:27 2016 Delaunay Marc
*/

#include <time.h>
#include <getopt.h>
#include <strings.h>

#include "server.h"
#include "list.h"

int	my_strcasecmp(const void *a, const void *b)
{
  return (strcasecmp((char *)a, (char *)b));
}

void		ser_del(void *this)
{
  t_server	*s;

  if (!this)
    return ;
  s = this;
  delete(s->parse_map);
  delete(s->command_map);
  delete(s->clients);
  delete(s->teams);
  delete(s->field);
  delete(s->graphics);
  if (s->fd)
    close(s->fd);
}
