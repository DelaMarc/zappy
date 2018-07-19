/*
** pair.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 16:38:58 2016 Loïc GIGOMAS
** Last update Sat Jun 11 16:41:24 2016 Loïc GIGOMAS
*/

#include "pair.h"

t_pair		*t_pair_new(t_pair_init var)
{
  t_pair	*p;

  if ((p = (t_pair *)new(t_object, sizeof(t_pair))) == NULL)
    return (NULL);
  p->first = var.first;
  p->second = var.second;
  return (p);
}
