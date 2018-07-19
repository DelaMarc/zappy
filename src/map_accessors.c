/*
** map.c for Zappy in /home/gigoma_l/rendu/PSU_2015_myirc/src
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sun Jun  5 08:52:19 2016 Loïc GIGOMAS
** Last update Sun Jun 12 00:30:24 2016 Loïc GIGOMAS
*/

#include "map.h"

size_t	map_size(t_map *m)
{
  return (m->size);
}

void		*map_get(t_map *m, void *key)
{
  size_t	i;

  for (i = 0; i < m->size; ++i)
    {
      if (m->array[i] && !m->compar(key, m->array[i]->first))
	return (m->array[i]->second);
    }
  return (m->defVal);
}
