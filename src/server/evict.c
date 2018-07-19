/*
** evict.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:11:52 2016 Delaunay Marc
** Last update Sun Jun 26 15:37:35 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"

static char	*graphic_evict(t_client *this, size_t size)
{
  char	*str;

  if ((str = malloc(size * 32 + 16)) == NULL)
    return (NULL);
  sprintf(str, "pex %zu\n", this->id);
  return (str);
}

int     evict_check(t_client *this, t_server *server, char *arg)
{
  int   val;

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_EVICT)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&evict;
      return (1);
    }
  return (0);
}

int		evict_players(t_client *this, t_field *s,
			      t_field *e, char *graphic)
{
  t_client	*dest;
  char		buffer[32];
  char		tmp[32];

  FOREACH(t_pair *, p, s->players)
    {
      dest = ((t_client *)p->second);
      if (dest->fd != this->fd)
	{
	  map_add(e->players, p->first, p->second);
	  map_remove(s->players, p->first);
	  sprintf(buffer, "deplacement: %d\n",
		  (this->dir - dest->dir + 2) * 2 + 1);
	  dest->x = this->x;
	  dest->y = this->y;
	  sprintf(tmp, "ppo %zu %d %d %d\n", dest->id,
		  dest->x, dest->y, GRAPHIC_DIR(dest->dir));
	  strcat(graphic, tmp);
	  write_iov(dest, buffer);
	  return (1);
	}
    }
  return (0);
}

int	evict(t_client *this, t_server *server, char *arg)
{
  int		x;
  int		y;
  t_field	*start;
  t_field	*end;
  char		*graphic;

  if (evict_check(this, server, arg))
    return (0);
  x = this->x;
  y = this->y;
  start = V2DGETP(t_field*, server->field, this->y, this->x);
  if ((graphic = graphic_evict(this, start->players->size - 1)) == NULL)
    return (3);
  move(this);
  end = V2DGETP(t_field*, server->field, this->y, this->x);
  while (evict_players(this, start, end, graphic));
  this->x = x;
  this->y = y;
  write_graphic(server, graphic);
  free(graphic);
  write_iov(this, "ok\n");
  (void)arg;
  return (0);
}
