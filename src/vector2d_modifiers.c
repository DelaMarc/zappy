/*
** vector2d_modifiers.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jun  7 23:24:20 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:33:55 2016 Loïc GIGOMAS
*/

#include "vector2d.h"

void	vec2d_del(void *ptr)
{
  if (!ptr)
    return ;
  vec_del((t_vector *)ptr);
}

t_vector2d	*t_vector2d_new(t_vector2d_init var)
{
  t_vector	*v;
  t_vector2d	*v2;

  if ((v2 = (t_vector2d *)new(t_object, sizeof(t_vector2d),
			      &vec2d_del)) == NULL)
    return (NULL);
  v = (t_vector *) v2;
  v->alloc = var.sizex * var.sizey + 1;
  v->size = v->alloc;
  v2->sx = var.sizex;
  v2->sy = var.sizey;
  if ((v->array = malloc(sizeof(void *) * (v->alloc))) == NULL)
    return (NULL);
  memset(v->array, 0, v->alloc * sizeof(void *));
  return (v2);
}
