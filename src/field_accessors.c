/*
** field_accessors.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 04:10:20 2016 Loïc GIGOMAS
** Last update Sat Jun 11 04:11:29 2016 Loïc GIGOMAS
*/

#include "field.h"

t_field		*field_size(t_field *f, int direction)
{
  if (!f || direction < 0 || direction >= 4)
    return (NULL);
  return (f->adjacent[direction]);
}
