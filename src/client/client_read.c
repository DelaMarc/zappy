/*
** client_read.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:35:30 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:36:27 2016 Loïc GIGOMAS
*/

#include <string.h>
#include <unistd.h>
#include "client/client.h"

static int	fill_str(char **str, char **ret, int *sl, int fd)
{
  int	r;
  char	buff[257];

  if ((r = read(fd, buff, 256)) < 0)
    return (5);
  if (r == 0)
    return (3);
  if ((*str = realloc(*str, *sl + r + 1)) == NULL)
    return (4);
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
      return (*str ? 1 : 0);
    }
  *ret = NULL;
  return (2);
}

/*
** Modifié pour avoir t_client * au lieu de fd (pour les statics)
** int	get_next_line(t_client *, char **str)
** return :
** 0 => no error, \n reached and ret filled
** 1 => no error, \n reached and ret filled, and str not null
** 2 => no error, \n not reached, ret = NULL
** 3 => EOF;
** 4 => malloc error
** 5 => read error
*/
int		get_next_line(t_client *c, int fd, char **ret)
{
  int		r;

  if (fd == -2)
    {
      free(c->read_tmp);
      return (0);
    }
  if (!c)
    return (3);
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
      return ((c->read_tmp ? 1 : 0));
    }
  if (fd == -1)
    return (2);
  return (fill_str(&c->read_tmp, ret, &c->read_size, fd));
}
