/*
** command_other.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:30:20 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:30:21 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include "client/ai.h"
#include "client/client.h"

int	command_expulse(t_client *c)
{
  char  *rep;

  rep = NULL;
  if (c->markov->step[COM_EXPUL] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_EXPUL] == 0)
    {
      printf("Expulse\n");
      write_iov(c, "expulse");
      ++c->markov->step[COM_EXPUL];
    }
  else if (c->markov->step[COM_EXPUL] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
        return (0);
      printf("Expulse: reçu '%s'\n", rep);
      ++c->markov->step[COM_EXPUL];
    }
  free(rep);
  return (0);
}

int	command_broadcast(t_client *c, char *msg)
{
  char  *rep;

  rep = NULL;
  if (c->markov->step[COM_BROADCST] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_BROADCST] == 0)
    {
      rep = malloc(12 + strlen(msg));
      sprintf(rep, "broadcast %s\n", msg);
      printf("Broadcast\n");
      write_iov(c, rep);
      ++c->markov->step[COM_BROADCST];
    }
  else if (c->markov->step[COM_BROADCST] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
        return (0);
      printf("Broadcast: reçu '%s'\n", rep);
      ++c->markov->step[COM_BROADCST];
    }
  free(rep);
  return (0);
}

int	command_incantation(t_client *c)
{
  char  *rep;

  rep = NULL;
  if (c->markov->step[COM_INCANT] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_INCANT] == 0)
    {
      printf("Incantation:\n");
      write_iov(c, "incantation\n");
      ++c->markov->step[COM_INCANT];
    }
  else if (c->markov->step[COM_INCANT] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
        return (0);
      printf("Incantation: reçu '%s'\n", rep);
      ++c->markov->step[COM_INCANT];
    }
  free(rep);
  return (0);
}

int	command_fork(t_client *c)
{
  char  *rep;

  rep = NULL;
  if (c->markov->step[COM_FORK] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_FORK] == 0)
    {
      printf("Fork\n");
      write_iov(c, "fork\n");
      ++c->markov->step[COM_FORK];
    }
  else if (c->markov->step[COM_FORK] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
        return (0);
      printf("Fork: reçu '%s'\n", rep);
      ++c->markov->step[COM_FORK];
    }
  free(rep);
  return (0);
}

int	command_slot(t_client *c)
{
  char  *rep;

  rep = NULL;
  if (c->markov->step[COM_SLOT] == 2)
    return (MARKOV_FINISHED);
  if (c->markov->step[COM_SLOT] == 0)
    {
      printf("Slot:\n");
      write_iov(c, "connect_nbr\n");
      ++c->markov->step[COM_SLOT];
    }
  else if (c->markov->step[COM_SLOT] == 1)
    {
      rep = CBGET(char *, c->received);
      if (!rep)
        return (0);
      printf("Slot: reçu '%s'\n", rep);
      c->slot = atoi(rep);
      ++c->markov->step[COM_SLOT];
    }
  free(rep);
  return (0);
}
