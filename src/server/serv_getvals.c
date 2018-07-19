/*
** serv_getvals.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Sun Jun 26 04:22:22 2016 Delaunay Marc
** Last update Sun Jun 26 23:38:14 2016 Loïc GIGOMAS
*/

#include <getopt.h>
#include "server.h"

int		varcmp(const void *s1, const void *s2)
{
  const char	ca = *(int *)s1;
  const char	cb = *(int *)s2;

  return (ca - cb);
}

int	intcmp(const void *a, const void *b)
{
  return ((int)((ssize_t)a - (ssize_t)b));
}

int	getPort(t_server *s, char **arg)
{
  if (!arg || (s->port = atoi(arg[optind++])) == -1)
    return (1);
  else
    return (0);
}

int	getX(t_server *s, char **arg)
{
  if ((s->x = atoi(arg[optind++])) < 3 ||
      s->x > 100)
    return (1);
  else
    return (0);
}

int	getY(t_server *s, char **arg)
{
  if ((s->y = atoi(arg[optind++])) < 3 ||
      s->y > 100)
    return (1);
  else
    return (0);
}
