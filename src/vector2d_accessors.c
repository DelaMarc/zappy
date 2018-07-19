/*
** vector2d_accessors.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jun  7 23:24:44 2016 Loïc GIGOMAS
** Last update Fri Jun 10 21:16:20 2016 Loïc GIGOMAS
*/

#include "vector2d.h"

size_t	vector2d_size(t_vector2d *v2)
{
  return (vector_size((t_vector *)v2));
}

size_t	vector2d_alloc(t_vector2d *v2)
{
  return (vector_alloc((t_vector *)v2));
}

size_t	vector2d_sizeX(t_vector2d *v2)
{
  return (v2->sx);
}

size_t	vector2d_sizeY(t_vector2d *v2)
{
  return (v2->sy);
}
