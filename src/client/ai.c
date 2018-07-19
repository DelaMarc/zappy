/*
** ai.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:29:51 2016 Loïc GIGOMAS
** Last update Sun Jun 26 23:20:06 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <errno.h>
#include "client/client.h"
#include "client/ai.h"

int	add_node(t_client *c, void *data)
{
  t_markov_node	*n;

  if ((n = new(t_markov_node, data)) == NULL)
    {
      fprintf(stderr, "add_node new error (%s)\n", strerror(errno));
      return (0);
    }
  if (vector_push_back(c->markov->nodes, n) != VEC_NOERR)
    {
      fprintf(stderr, "add_node push_back error (%s)\n", strerror(errno));
      return (0);
    }
  return (1);
}

int	add_link(t_markov_node *n, size_t min, size_t max, size_t i)
{
  t_markov_link	*l;

  if ((l = new(t_markov_link, i, min, max)) == NULL)
    {
      fprintf(stderr, "add_link new error (%s)\n", strerror(errno));
      return (0);
    }
  if (vector_push_back(n->links, l) != VEC_NOERR)
    {
      fprintf(stderr, "add_link push_back error (%s)\n", strerror(errno));
      return (0);
    }
  return (1);
}

/*
** Nodes are created in the order of the t_aiNodes enum.
*/
static int	ai_nodes(t_client *c)
{
  if (!add_node(c, &state_initial) ||
      !add_node(c, &command_avance) ||
      !add_node(c, &command_droite) ||
      !add_node(c, &command_gauche) ||
      !add_node(c, &command_voir) ||
      !add_node(c, &command_inventaire) ||
      !add_node(c, &state_take_food) ||
      !add_node(c, &command_expulse) ||
      !add_node(c, &command_broadcast) ||
      !add_node(c, &command_prendre) ||
      !add_node(c, &command_poser) ||
      !add_node(c, &command_incantation) ||
      !add_node(c, &command_fork) ||
      !add_node(c, &command_slot))
    return (0);
  return (1);
}

static int	ai_links(t_client *c)
{
  t_markov_node	*n;

  n = VGETP(t_markov_node *, c->markov->nodes, INITIAL);
  if (!add_link(n, 0, 1000, COM_FORWARD))
    return (0);
  n = VGETP(t_markov_node *, c->markov->nodes, COM_FORWARD);
  if (!add_link(n, 0, 1000, COM_INV))
    return (0);
  n = VGETP(t_markov_node *, c->markov->nodes, COM_INV);
  if (!add_link(n, 0, 1000, COM_SEE))
    return (0);
  n = VGETP(t_markov_node *, c->markov->nodes, COM_SEE);
  if (!add_link(n, 0, 1000, TAKEFOOD))
    return (0);
  return (ai_links_1(c));
}

int		set_ai(t_client *c)
{
  if (!c || !ai_nodes(c) || !ai_links(c))
    return (0);
  vector_push_back(c->markov->mandat, new(t_markov_node, &mandat));
  c->markov->init_state[TAKEFOOD] = &init_take_food;
  return (1);
}
