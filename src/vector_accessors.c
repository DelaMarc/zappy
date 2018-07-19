/*
** vector_accessors.c for Zapy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jun 10 21:16:09 2016 Loïc GIGOMAS
** Last update Fri Jun 10 21:16:11 2016 Loïc GIGOMAS
*/

#include "vector.h"

size_t	vector_size(t_vector *v)
{
  if (!v)
    return (0);
  return (v->size);
}

size_t	vector_alloc(t_vector *v)
{
  if (!v)
    return (0);
  return (v->alloc);
}

void	*vector_at(t_vector *v, size_t index)
{
  if (!v || index >= v->size)
    return (NULL);
  return (v->array[index]);
}
