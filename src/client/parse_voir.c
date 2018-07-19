/*
** parse_reply.c for parse in /home/pawele_t/PSU_2015_zappy/src/client
** 
** Made by Pawelec Théo
** Login   <pawele_t@epitech.net>
** 
** Started on  Sat Jun 25 01:55:07 2016 Pawelec Théo
** Last update Sat Jun 25 05:20:46 2016 Pawelec Théo
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stones.h"
#include "client/client.h"

int	vision_depth(int lvl)
{
  int	res;
  int	depth;

  res = 0;
  depth = 1;
  while (lvl >= 0)
    {
      res += depth;
      depth += 2;
      lvl--;
    }
  return (res);
}

void	clear_state(int *row)
{
  int	i;

  i = 0;
  while (i < 8)
    {
      row[i] = 0;
      i++;
    }
}

void	update_row(int *row, char *buf)
{
  int	stoneId;

  stoneId = 0;
  while (stoneId <= STONE_NBR)
    {
      if (stoneId < STONE_NBR && strcmp(buf, stoneName[stoneId]) == 0)
	row[stoneId] += 1;
      else if (stoneId == STONE_NBR && strcmp(buf, "joueur") == 0)
	row[stoneId] += 1;
      stoneId++;
    }
}

int	update_sight(int *row, char *rep)
{
  int	i;
  int	len;
  char	*buf;

  i = 0;
  buf = NULL;
  while (rep[i] != 0 && rep[i] != ',')
    {
      while (rep[i] == ' ')
	i++;
      len = 0;
      while (rep[i + len] != ' ' && rep[i + len] != ',' && rep[i + len] != '}')
        len++;
      if (len > 0)
	{
	  buf = strndup(rep + i, len);
	  update_row(row, buf);
	  free(buf);
	}
      if (rep[i + len] == ',')
	return (i + len + 1);
      i += len + 1;
    }
  return (i == 0 ? 1 : i);
}
