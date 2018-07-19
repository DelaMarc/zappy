/*
** team_modifiers.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 01:45:00 2016 Loïc GIGOMAS
** Last update Thu Jun 23 18:34:00 2016 Delaunay Marc
*/

#include "team.h"

t_team		*t_team_new(t_team_init var)
{
  t_team	*t;

  if (!var.name)
    return (NULL);
  if ((t = (t_team *)new(t_object, sizeof(t_team), &tea_del)) == NULL)
    return (NULL);
  if ((t->players = new(t_map, &client_cmp)) == NULL)
    return (NULL);
  if ((t->eggs = new(t_list, 10)) == NULL)
    return (NULL);
  t->name = var.name;
  t->maxConn = var.maxConnexions;
  return (t);
}

void		tea_del(void *ptr)
{
  t_team	*t;

  if (!ptr)
    return ;
  t = ptr;
  delete(t->players);
  delete(t->eggs);
}

int		team_add_player(t_team *t, t_player *p)
{
  if (!t || !p)
    return (TEAM_ARG);
  return (map_add(t->players, p->client, p));
}

int		team_remove_player(t_team *t, t_player *p)
{
  if (!t || !p)
    return (TEAM_ARG);
  return (map_remove(t->players, p->client));
}

int		team_set_maxConn(t_team *t, size_t mc)
{
  if (!t || mc == 0)
    return (TEAM_ARG);
  t->maxConn = mc;
  return (TEAM_NOERR);
}
