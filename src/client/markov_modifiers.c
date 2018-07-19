/*
** markov_modifiers.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:28:53 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:28:54 2016 Loïc GIGOMAS
*/

#include <stdlib.h>
#include "client/markov.h"

t_markov	*t_markov_new(t_markov_init var)
{
  t_markov	*m;

  if ((m = (t_markov *)new(t_object, sizeof(t_markov))) == NULL)
    return (NULL);
  if ((m->nodes = new(t_vector, var.n_nodes)) == NULL)
    return (NULL);
  if ((m->mandat = new(t_vector, var.n_mandat)) == NULL)
    return (NULL);
  srand48_r(var.seed, &m->dr48);
  return (m);
}

t_markov_link	*t_markov_link_new(t_markov_link_init var)
{
  t_markov_link	*l;

  if (!var.child)
    return (NULL);
  if ((l = (t_markov_link *)new(t_object, sizeof(t_markov_link))) == NULL)
    return (NULL);
  l->node = var.child;
  l->t_min = var.t_min;
  l->t_max = var.t_max;
  return (l);
}

t_markov_node	*t_markov_node_new(t_markov_node_init var)
{
  t_markov_node	*n;

  if (!var.data)
    return (NULL);
  if ((n = (t_markov_node *)new(t_object, sizeof(t_markov_node))) == NULL)
    return (NULL);
  if ((n->links = new(t_vector)) == NULL)
    return (NULL);
  n->data = var.data;
  return (n);
}
