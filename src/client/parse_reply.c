/*
** parse_reply.c for parse in /home/pawele_t/PSU_2015_zappy/src/client
**
** Made by Pawelec Théo
** Login   <pawele_t@epitech.net>
**
** Started on  Sat Jun 25 01:55:07 2016 Pawelec Théo
** Last update Sun Jun 26 21:09:03 2016 Loïc GIGOMAS
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stones.h"
#include "client/client.h"

void	parse_inventaire(t_client *c, char *rep)
{
  int	i;
  int	x;

  i = 0;
  x = 0;
  while (rep[i] != 0 && x < STONE_NBR)
    {
      if (rep[i] >= '0' && rep[i] <= '9')
	{
	  c->inv[x] = atoi(rep + i);
	  x++;
	  while (rep[i] >= '0' && rep[i] <= '9')
	    i++;
	}
      i++;
    }
}

void	parse_voir(t_client *c, char *rep)
{
  int   i;
  int	cases;
  int   rhead;

  i = 0;
  rhead = 0;
  cases = vision_depth(c->lvl);
  while (i < cases)
    {
      clear_state(c->sight[i]);
      rhead += update_sight(c->sight[i], rep + rhead);
      i++;
    }
}
