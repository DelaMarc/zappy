/*
** client_accessors.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 17:26:02 2016 Loïc GIGOMAS
** Last update Sat Jun 11 17:26:03 2016 Loïc GIGOMAS
*/

#include "client.h"

int			client_cmp(const void *a, const void *b)
{
  const t_client	*ca = a;
  const t_client	*cb = b;

  if (!a || !b)
    return (-1);
  return (ca->fd - cb->fd);
}
