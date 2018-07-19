/*
** gnl.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jun 21 21:03:08 2016 Loïc GIGOMAS
** Last update Tue Jun 21 21:11:18 2016 Delaunay Marc
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
** int	get_next_line(int fd, char **str)
** return :
** 0 => no error, \n reached and ret filled
** 1 => no error, \n not reached, ret = NULL
** 2 => EOF;
** 3 => malloc error
** 4 => read error
*/
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

int		get_next_line(int fd, char **ret)
{
  static char	*str = NULL;
  static int	sl = 0;
  int		r;

  if (str && (r = strcspn(str, "\n")) < sl)
    {
      *ret = str;
      (*ret)[r] = 0;
      sl -= (r + 1);
      if (sl < 0)
	sl = 0;
      if (sl > 0)
	str = strdup(&str[r + 1]);
      else
	str = NULL;
      return (0);
    }
  return (fill_str(&str, ret, &sl, fd));
}
