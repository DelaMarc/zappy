/*
** markov_accessors.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:30:10 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:38:13 2016 Loïc GIGOMAS
*/

#include "foreach.h"
#include "client/client.h"
#include "client/markov.h"
#include "client/ai.h"

int	markov_mandat(t_markov *m, void *params)
{
  int	i;

  if (!m)
    return (1);
  FOREACH(t_markov_node *, n, m->mandat)
    if ((i = ((t_state_f)n->data)(params)) != 0)
      return (i);
  return (0);
}

t_markov_node	*markov_next(t_markov *m, void*p)
{
  t_markov_node	*n;
  t_markov_link	*l;
  size_t	rnd;
  size_t	i;

  if (!m)
    return (NULL);
  n = VGETP(t_markov_node *, m->nodes, m->actual);
  if (n && n->links->size > 0)
    {
      lrand48_r(&m->dr48, (long int *)&rnd);
      rnd = rnd % 1000;
      for (i = 0; i < n->links->size; ++i)
	if ((l = VGETP(t_markov_link *, n->links, i)) &&
	    l->t_min <= rnd && rnd < l->t_max)
	  {
	    m->step[m->actual] = 0;
	    if (m->init_state[m->actual])
	      m->init_state[m->actual](p);
	    m->actual = l->node;
	    return (VGETP(t_markov_node *, m->nodes, l->node));
	  }
    }
  return (NULL);
}
