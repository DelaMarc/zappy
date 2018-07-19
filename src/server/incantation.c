/*
** incantation.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:19:45 2016 Delaunay Marc
** Last update Sun Jun 26 17:03:41 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"

const unsigned int	need[7][STONE_NBR + 1] = {{ 1, 0, 1, 0, 0, 0, 0, 0 },
						  { 2, 0, 1, 1, 1, 0, 0, 0 },
						  { 2, 0, 2, 0, 1, 0, 2, 0 },
						  { 4, 0, 1, 1, 2, 0, 1, 0 },
						  { 4, 0, 1, 2, 1, 3, 0, 0 },
						  { 6, 0, 1, 2, 3, 0, 1, 0 },
						  { 6, 0, 2, 2, 2, 2, 2, 1 }};

static int	graphic_incantation_end(t_client *this, t_server *server,
					int res, t_field *f)
{
  char		*msg;
  char		*map;
  char		buff[32];
  t_client	*tmp;

  if ((map = mct(server, NULL)) == NULL)
    return (3);
  if ((msg = malloc(strlen(map) + (f->players->size * 24) + 16)) == NULL)
    return (3);
  sprintf(msg, "pie %d %d %d\n", this->x, this->y, res);
  FOREACH(t_pair *, p, f->players)
    {
      tmp = (t_client *)p->second;
      sprintf(buff, "plv %zu %d\n", tmp->id, tmp->lvl);
      strcat(msg, buff);
    }
  strcat(msg, map);
  write_graphic(server, msg);
  free(msg);
  free(map);
  return (0);
}

int			incantation_is_possible(t_field *field, t_client *this)
{
  int	i;

  i = 0;
  if (field->players->size != need[this->lvl - 1][0])
    return (0);
  FOREACH(t_pair *, tmp, field->players)
    {
      if (((t_client*)tmp->second)->lvl != this->lvl)
	return (0);
    }
  while (i < STONE_NBR)
    {
      if (field->stone[i] != need[this->lvl - 1][i + 1])
	return (0);
      i++;
    }
  return (1);
}

static int	graphic_incantation(t_field *f, t_server *server, t_client *this)
{
  char	buff[256];
  char	str_id[32];

  buff[0] = '\0';
  sprintf(str_id, "pic %d %d %d", this->x, this->y, this->lvl);
  strcat(buff, str_id);
  FOREACH(t_pair *, p, f->players)
    {
      sprintf(str_id, " %zu", (size_t)((t_client *)p->second)->id);
      strcat(buff, str_id);
      write_iov(p->second, "elevation en cours\n");
    }
  strcat(buff, "\n");
  write_graphic(server, buff);
  this->ptr_func = (void*)&incantation;
  return (1);
}

int             incantation_check(t_client *this, t_server *server, char *arg)
{
  int           val;
  t_field       *f;

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if (!incantation_is_possible((f = V2DGETP(t_field*, server->field, this->y,
                                            this->x)), this)
      || (val = commands_set_timer(this, server, TIME_INCANTATION)) == 0)
    {
      write_iov(this, "ko\n");
      return (graphic_incantation_end(this, server, 0, f) + 1);
    }
  else if (val == 1)
    return (graphic_incantation(f, server, this));
  return (0);
}

int	incantation(t_client *this, t_server *server, char *arg)
{
  t_field	*f;
  int		i;
  char		buff[128];

  if ((i = incantation_check(this, server, arg)))
    return ((i == 4) ? 3 : i);
  f = V2DGETP(t_field*, server->field, this->y, this->x);
  i = 0;
  while (i < STONE_NBR)
    {
      f->stone[i] -= need[this->lvl -1][i + 1];
      i++;
    }
  FOREACH(t_pair *, p, f->players)
    {
      ((t_client*)p->second)->lvl++;
      if (((t_client*)p->second)->lvl == 8)
	((t_client*)p->second)->team->masters++;
      if (((t_client*)p->second)->team->masters >= 6 && server->run)
	graphic_end(server, ((t_client*)p->second)->team->name);
      sprintf(buff, "niveau actuel : %d\n", ((t_client*)p->second)->lvl);
      write_iov(p->second, buff);
    }
  return (graphic_incantation_end(this, server, 1, f));
}
