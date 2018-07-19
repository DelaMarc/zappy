/*
** team_accessors.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 01:44:51 2016 Loïc GIGOMAS
** Last update Sat Jun 11 01:44:53 2016 Loïc GIGOMAS
*/

#include "team.h"

t_map		*team_players(t_team *t)
{
  if (!t)
    return (NULL);
  return (t->players);
}

char		*team_name(t_team *t)
{
  if (!t)
    return ("(null)");
  return (t->name);
}

size_t		team_maxConn(t_team *t)
{
  if (!t)
    return (0);
  return (t->maxConn);
}
