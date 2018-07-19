/*
** list.c for Zappy in /home/gigoma_l/rendu/PSU_2015_myirc/src
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sun Jun  5 08:52:19 2016 Loïc GIGOMAS
** Last update Wed Jun 22 15:35:00 2016 Loïc GIGOMAS
*/

#include "list.h"

size_t	list_size(t_list *l)
{
  return (l->size);
}

void		*list_get(t_list *m, size_t index)
{
  if (!m || index >= m->size)
    return (NULL);
  return (m->array[index]);
}
