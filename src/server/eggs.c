/*
** eggs.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Wed Jun 22 15:26:12 2016 Delaunay Marc
** Last update Sun Jun 26 23:15:28 2016 Loïc GIGOMAS
*/

#include "server.h"
#include "foreach.h"

static void	manage_timer_step2(t_team *tmp, t_server *server,
				   t_egg *t, size_t i)
{
  char		buff[24];

  if (timer_finished(t->timer))
    {
      if (!(t->ghost))
	{
	  sprintf(buff, "eht %zu\n", t->id);
	  write_graphic(server, buff);
	  t->ghost = 1;
	  tmp->maxConn++;
	  set_timer(t->timer, TTIME(1386, server->time));
	}
      else
	{
	  --tmp->maxConn;
	  sprintf(buff, "edi %zu\n", t->id);
	  write_graphic(server, buff);
	  list_remove(tmp->eggs, i);
	}
    }
}

static void	manage_timer(t_team *tmp, t_server *server)
{

  t_egg		*t;
  size_t	i;

  for (i = 0; i < tmp->eggs->size; ++i)
    {
      t = list_get(tmp->eggs, i);
      manage_timer_step2(tmp, server, t, i);
    }
}

void		manage_eggs(t_server *server)
{
  FOREACH(t_team *, tmp, server->teams)
    {
      if (tmp->eggs->size)
	manage_timer(tmp, server);
    }
}
