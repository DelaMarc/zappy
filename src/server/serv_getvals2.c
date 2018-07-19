/*
** serv_getvals2.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Sun Jun 26 04:21:51 2016 Delaunay Marc
** Last update Sun Jun 26 23:34:23 2016 Loïc GIGOMAS
*/

#include <getopt.h>
#include "server.h"

int	getTeams(t_server *s, char **arg)
{
  for (; arg[optind] && arg[optind][0] != '-'; ++optind)
    if (vector_push_back(s->teams, new(t_team, arg[optind])) != VEC_NOERR)
      return (1);
  return (0);
}

int	getNbc(t_server *s, char **arg)
{
  if ((s->clients_max = atoi(arg[optind])) == -1)
    return (1);
  else
    return (0);
}

int	getT(t_server *s, char **arg)
{
  s->time = atoi(arg[optind]);
  if (s->time <= 0)
    s->time = 1;
  if (s->time > 1000)
    s->time = 1000;
  return (0);
}

int	afk(t_server *s, char **arg)
{
  (void)s;
  (void)arg;
  return (0);
}
