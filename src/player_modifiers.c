/*
** player_modifiers.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 00:51:44 2016 Loïc GIGOMAS
** Last update Sat Jun 11 03:31:26 2016 Loïc GIGOMAS
*/

#include "player.h"

t_player	*t_player_new(t_player_init var)
{
  t_player	*p;

  if (!var.team || !var.field || !var.client)
    return (NULL);
  if ((p = (t_player *)new(t_object, sizeof(t_player), NULL)) == NULL)
    return (NULL);
  p->team = var.team;
  p->field = var.field;
  p->client = var.client;
  return (p);
}

void		player_addStone(t_player *p, t_stoneType type)
{
  if (p && type >= 0 && type < STONE_NBR)
    ++p->stone[type];
}

void		player_remStone(t_player *p, t_stoneType type)
{
  if (p && type >= 0 && type < STONE_NBR && p->stone[type] > 0)
    --p->stone[type];
}
