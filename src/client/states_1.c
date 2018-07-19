/*
** states_1.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:28:16 2016 Loïc GIGOMAS
** Last update Sun Jun 26 21:04:50 2016 Loïc GIGOMAS
*/

#include <unistd.h>
#include <stdio.h>
#include "client/ai.h"

void	init_take_food(void *p)
{
  t_client	*c;

  if (!p)
    return;
  c = p;
  c->markov->step[COM_TAKE] = 0;
}

int	state_take_food(t_client *c)
{
  if (c->inv[nourriture] <= 100 && c->sight[0][nourriture])
    return (command_prendre(c, "nourriture"));
  return (MARKOV_FINISHED);
}

static int	state_init_team(t_client *c)
{
  char	*rep;

  rep = CBGET(char *, c->received);
  if (!rep)
    return (0);
  if (strcasecmp(rep, "BIENVENUE"))
    {
      free(rep);
      return (0);
    }
  write_iov(c, c->team);
  free(rep);
  return (1);
}

int	state_initial(t_client *c)
{
  char	*rep;

  rep = NULL;
  if (c->markov->step[INITIAL] == 3)
    return (MARKOV_FINISHED);
  if (c->markov->step[INITIAL] == 0)
    {
      if (state_init_team(c))
	++c->markov->step[INITIAL];
    }
  else if (c->markov->step[INITIAL] == 1)
    {
      if (!(rep = CBGET(char *, c->received)))
	return (0);
      ++c->markov->step[INITIAL];
    }
  else
    {
      if (!(rep = CBGET(char *, c->received)))
	return (0);
      ++c->markov->step[INITIAL];
      printf("Connexion etablished\n");
    }
  free(rep);
  return (0);
}
