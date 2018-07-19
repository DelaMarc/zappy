/*
** mandat.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:28:58 2016 Loïc GIGOMAS
** Last update Sun Jun 26 23:24:08 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <strings.h>
#include "foreach.h"
#include "client/ai.h"
#include "client/client.h"

int	mandat(t_client *c)
{
  int	dead;
  char	*str;

  dead = 0;
  if (c->received->remain < c->received->alloc)
    {
      FOREACH(char *, str, c->received)
	if (str && !strcasecmp(str, "mort"))
	  {
	    dead = 1;
	    break;
	  }
      if (dead)
	{
	  printf("Le joueur est mort !\n");
	  while ((str = CBGET(char *, c->received)))
	    free(str);
	  get_next_line(c, -2, NULL);
	  for (; c->iovcnt; )
	    free(c->io[--c->iovcnt].iov_base);
	}
    }
  return (dead);
}
