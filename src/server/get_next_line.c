/*
** get_next_line.c for  in /home/delaun_m/clones/PSU_2015_zappy
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 03:20:34 2016 Delaunay Marc
** Last update Sun Jun 26 03:20:58 2016 Delaunay Marc
*/

#include "client.h"

static int	fill_str(char **str, char **ret, int *sl, int fd)
{
  int	r;
  char	buff[257];

  if ((r = read(fd, buff, 256)) < 0)
    return (4);
  if (r == 0)
    return (2);
  if ((*str = realloc(*str, *sl + r + 1)) == NULL)
    return (3);
  buff[r] = 0;
  (*str)[*sl] = 0;
  *str = strcat(*str, buff);
  *sl = strlen(*str);
  if ((r = strcspn(*str, "\n")) < *sl)
    {
      *ret = *str;
      (*ret)[r] = 0;
      if ((*sl -= (r + 1)) > 0)
	*str = strdup(&(*str)[r + 1]);
      else
	*str = NULL;
      return (0);
    }
  *ret = NULL;
  return (1);
}

int		get_next_line(t_client *c, char **ret)
{
  int		r;

  if (!c)
    return (2);
  if (c->read_tmp && (r = strcspn(c->read_tmp, "\n")) < c->read_size)
    {
      *ret = c->read_tmp;
      (*ret)[r] = 0;
      c->read_size -= (r + 1);
      if (c->read_size < 0)
	c->read_size = 0;
      if (c->read_size > 0)
	c->read_tmp = strdup(&(c->read_tmp)[r + 1]);
      else
	c->read_tmp = NULL;
      return (0);
    }
  return (fill_str(&c->read_tmp, ret, &c->read_size, c->fd));
}
