/*
** ai_links.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:30:27 2016 Loïc GIGOMAS
** Last update Sun Jun 26 23:18:37 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <errno.h>
#include "client/client.h"
#include "client/ai.h"

int	ai_links_1(t_client *c)
{
  t_markov_node	*n;

  n = VGETP(t_markov_node *, c->markov->nodes, TAKEFOOD);
  if (!add_link(n, 0, 700, COM_FORWARD) ||
     !add_link(n, 700, 850, COM_LEFT) ||
     !add_link(n, 850, 1000, COM_RIGHT))
    return (0);
  n = VGETP(t_markov_node *, c->markov->nodes, COM_LEFT);
  if (!add_link(n, 0, 850, COM_FORWARD) ||
      !add_link(n, 850, 925, COM_RIGHT) ||
      !add_link(n, 925, 1000, COM_LEFT))
    return (0);
  n = VGETP(t_markov_node *, c->markov->nodes, COM_RIGHT);
  if (!add_link(n, 0, 850, COM_FORWARD) ||
      !add_link(n, 850, 925, COM_LEFT) ||
      !add_link(n, 925, 1000, COM_RIGHT))
    return (0);
  return (1);
}
