/*
** see.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:21:04 2016 Delaunay Marc
** Last update Sun Jun 26 04:21:05 2016 Delaunay Marc
*/

#include "server.h"

int     see_check(t_client *this, t_server *server, char *arg)
{
  int   val;

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_SEE)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&see;
      return (1);
    }
  return (0);
}

void	see_add_stones(t_field *field, char *stones)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (i < STONE_NBR)
    {
      if (field->stone[i] > 0)
        {
          j = 0;
          while (j < field->stone[i])
            {
	      strcat(stones, " ");
              strcat(stones, stoneName[i]);
              j++;
            }
        }
      i++;
    }
}

void		see_add_player(t_field *field, char *stones)
{
  size_t	i;

  i = 0;
  while (i < field->players->size)
    {
      strcat(stones, " player");
      i++;
    }
  see_add_stones(field, stones);
}

void	fill_stone(t_client *this, t_server *server, char *stones, int r)
{
  int	c;
  int	neg;

  c = 0;
  while (c < r * 2 + 1)
    {
      if (r)
	strcat(stones, ",");
      neg = (1 - ((this->dir + 1) & 2));
      see_add_player(V2DGETP(t_field*, server->field,
			     MOD((this->y + TRIPOSY(r, c, this->dir, neg)),
				 server->field->sx),
			     MOD((this->x + TRIPOSX(r, c, this->dir, neg)),
				 server->field->sx)), stones);
      c++;
    }
}

int	see(t_client *this, t_server *server, char *arg)
{
  int	r;
  char  stones[8192];

  if (see_check(this, server, arg))
    return (0);
  r = 0;
  stones[0] = '\0';
  strcat(stones, "{");
  while (r <= this->lvl)
    {
      fill_stone(this, server, stones, r);
      r++;
    }
  strcat(stones, "}\n");
  write_iov(this, stones);
  return (0);
}
