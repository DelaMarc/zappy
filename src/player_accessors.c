/*
** player_accessors.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 00:51:38 2016 Loïc GIGOMAS
** Last update Sat Jun 11 03:30:41 2016 Loïc GIGOMAS
*/

#include "player.h"

t_team		*player_team(t_player *p)
{
  if (!p)
    return (NULL);
  return (p->team);
}

t_field		*player_field(t_player *p)
{
  if (!p)
    return (NULL);
  return (p->field);
}

__uint16_t	player_getStone(t_player *p, t_stoneType type)
{
  if (p && type >= 0 && type < STONE_NBR)
    return (p->stone[type]);
  return (0);
}
