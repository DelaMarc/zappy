/*
** graphic_cmd2.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:19:21 2016 Delaunay Marc
** Last update Sun Jun 26 16:42:08 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"

char	*ppo(t_server *server, char *arg)
{
  t_client	*t;
  int		id;
  char		buff[64];

  id = atoi(arg);
  FOREACH(t_pair *, tmp, server->clients)
    {
      t = ((t_client *)tmp->second);
      if ((int)t->id == id)
	{
	  sprintf(buff, "ppo %zu %d %d %d\n", t->id, t->x, t->y,
		  GRAPHIC_DIR(t->dir));
	  return (strdup(buff));
	}
    }
  return (strdup("sbp\n"));
}

char	*plv(t_server *server, char *arg)
{
  t_client	*t;
  int		id;
  char		buff[64];

  id = atoi(arg);
  FOREACH(t_pair *, tmp, server->clients)
    {
      t = ((t_client *)tmp->second);
      if ((int)t->id == id)
	{
	  sprintf(buff, "plv %zu %d\n", t->id, t->lvl);
	  return (strdup(buff));
	}
    }
  return (strdup("sbp\n"));
}

char	*pin(t_server *server, char *arg)
{
  t_client	*t;
  int		id;
  char		buff[128];

  id = atoi(arg);
  FOREACH(t_pair *, tmp, server->clients)
    {
      t = ((t_client *)tmp->second);
      if ((int)t->id == id)
	{
	  sprintf(buff, "pin %zu %d %d %d %d %d %d %d %d %d\n", t->id, t->x,
		  t->y, t->inv[0], t->inv[1], t->inv[2], t->inv[3], t->inv[4],
		  t->inv[5], t->inv[6]);
	  return (strdup(buff));
	}
    }
  return (strdup("sbp\n"));
}

char	*sgt(t_server *server, char *arg)
{
  char	buff[16];

  (void)arg;
  sprintf(buff, "sgt %d\n", (int)server->time);
  return (strdup(buff));
}

char	*sst(t_server *server, char *arg)
{
  int	t;

  t = atoi(arg);
  if (t > 0)
    {
      server->time = t;
      return (sgt(server, arg));
    }
  return (strdup("sbp\n"));
}
