/*
** command_objet.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:29:40 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:29:41 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <string.h>
#include "client/ai.h"
#include "client/client.h"

int	command_voir(t_client *c)
{
  char	*rep;

  rep = NULL;
  if (c->markov->step[COM_SEE] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_SEE] == 0)
    {
      printf("Voir\n");
      write_iov(c, "voir\n");
      ++c->markov->step[COM_SEE];
    }
  else if (c->markov->step[COM_SEE] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Voir : '%s'\n", rep);
      parse_voir(c, rep);
      ++c->markov->step[COM_SEE];
    }
  free(rep);
  return (0);
}

int	command_inventaire(t_client *c)
{
    char	*rep;

  rep = NULL;
  if (c->markov->step[COM_INV] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_INV] == 0)
    {
      printf("Inventaire\n");
      write_iov(c, "inventaire\n");
      ++c->markov->step[COM_INV];
    }
  else if (c->markov->step[COM_INV] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Inventaire : '%s'\n", rep);
      parse_inventaire(c, rep);
      ++c->markov->step[COM_INV];
    }
  free(rep);
  return (0);
}

int	command_prendre(t_client *c, char *obj)
{
    char	*rep;

  rep = NULL;
  if (c->markov->step[COM_TAKE] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_TAKE] == 0)
    {
      rep = malloc(8 + strlen(obj));
      sprintf(rep, "prend %s\n", obj);
      printf("Prendre ('%s')\n", obj);
      write_iov(c, rep);
      ++c->markov->step[COM_TAKE];
    }
  else if (c->markov->step[COM_TAKE] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Prendre : reçu '%s'\n", rep);
      ++c->markov->step[COM_TAKE];
    }
  free(rep);
  return (0);
}

int	command_poser(t_client *c, char *obj)
{
  char	*rep;

  rep = NULL;
  if (c->markov->step[COM_PUT] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_PUT] == 0)
    {
      rep = malloc(8 + strlen(obj));
      sprintf(rep, "pose %s\n", obj);
      printf("Pose: ('%s')\n", obj);
      write_iov(c, rep);
      ++c->markov->step[COM_PUT];
    }
  else if (c->markov->step[COM_PUT] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
	return (0);
      printf("Pose: reçu '%s'\n", rep);
      ++c->markov->step[COM_PUT];
    }
  free(rep);
  return (0);
}
