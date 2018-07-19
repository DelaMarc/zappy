/*
** field_modifiers.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 03:57:59 2016 Loïc GIGOMAS
** Last update Sat Jun 11 04:13:20 2016 Loïc GIGOMAS
*/

#include "field.h"

t_field		*t_field_new(t_field_init var)
{
  t_field	*f;

  if ((f = (t_field *)new(t_object, sizeof(t_field), &fie_del)) == NULL)
    return (NULL);
  if ((f->players = new(t_map, &client_cmp)) == NULL)
    return (NULL);
  f->y = var.y;
  f->x = var.x;
  return (f);
}

void		fie_del(void *ptr)
{
  t_field	*f;

  if (!ptr)
    return ;
  f = ptr;
  delete(f->players);
}

int		field_adjacents(t_field *f, t_field *adj[4])
{
  if (!f || !adj[0] || !adj[1] || !adj[2] || !adj[3])
    return (FIELD_ARGS);
  f->adjacent[0] = adj[0];
  f->adjacent[1] = adj[1];
  f->adjacent[2] = adj[2];
  f->adjacent[3] = adj[3];
  return (FIELD_NOERR);
}
