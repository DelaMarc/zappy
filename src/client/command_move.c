/*
** command_move.c for command_move in /home/pawele_t/PSU_2015_zappy/src/client
**
** Made by Pawelec Théo
** Login   <pawele_t@epitech.net>
**
** Started on  Fri Jun 24 19:07:44 2016 Pawelec Théo
** Last update Sat Jun 25 21:15:01 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <string.h>
#include "client/ai.h"
#include "client/client.h"

int	command_avance(t_client *c)
{
  char	*rep;

  rep = NULL;
  if (c->markov->step[COM_FORWARD] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_FORWARD] == 0)
    {
      printf("Avance\n");
      write_iov(c, "avance\n");
      ++c->markov->step[COM_FORWARD];
    }
  else if (c->markov->step[COM_FORWARD] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Avance: reçu '%s'\n", rep);
      ++c->markov->step[COM_FORWARD];
    }
  free(rep);
  return (MARKOV_CONTINUE);
}

int	command_droite(t_client *c)
{
  char	*rep;

  rep = NULL;
  if (c->markov->step[COM_RIGHT] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_RIGHT] == 0)
    {
      printf("Droite\n");
      write_iov(c, "droite\n");
      ++c->markov->step[COM_RIGHT];
    }
  else if (c->markov->step[COM_RIGHT] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Droite: reçu '%s'\n", rep);
      ++c->markov->step[COM_RIGHT];
    }
  free(rep);
  return (0);
}

int	command_gauche(t_client *c)
{
  char	*rep;

  rep = NULL;
  if (c->markov->step[COM_LEFT] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_LEFT] == 0)
    {
      printf("Gauche\n");
      write_iov(c, "gauche\n");
      ++c->markov->step[COM_LEFT];
    }
  else if (c->markov->step[COM_LEFT] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Gauche: reçu '%s'\n", rep);
      ++c->markov->step[COM_LEFT];
    }
  free(rep);
  return (0);
}
