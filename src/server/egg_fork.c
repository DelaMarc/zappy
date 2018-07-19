/*
** egg_fork.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:18:32 2016 Delaunay Marc
** Last update Sun Jun 26 15:36:59 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"
#include "egg.h"

void	egg_del(void *s)
{
  t_egg	*this;

  this = (t_egg *)s;
  delete(this->timer);
}

t_egg		*t_egg_new(t_egg_init var)
{
  t_egg		*new;
  static size_t	id = 0;

  if (!var.s || !var.client->team)
    return (NULL);
  if ((new = (t_egg *)new(t_object, sizeof(t_egg), &egg_del)) == NULL)
    return (NULL);
  if ((new->timer = new(t_timer, TTIME(600, var.s->time))) == NULL)
    return (NULL);
  new->team = var.client->team;
  new->x = var.client->x;
  new->y = var.client->y;
  new->id = id;
  ++id;
  return (new);
}

int     egg_fork_check(t_client *this, t_server *server, char *arg)
{
  int   val;
  char	buffer[24];

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_EGG_FORK)) == 0)
    return (1);
  else if (val == 1)
    {
      sprintf(buffer, "pfk %zu\n", this->id);
      write_graphic(server, buffer);
      this->ptr_func = (void*)&egg_fork;
      return (1);
    }
  return (0);
}

int	egg_fork(t_client *this, t_server *server, char *arg)
{
  t_egg	*egg;
  char	buffer[24];

  if (egg_fork_check(this, server, arg))
    return (0);
  if ((egg = new(t_egg, this, server)) == NULL)
    return (1);
  list_add(this->team->eggs, egg, 0);
  sprintf(buffer, "enw %zu %zu %d %d\n",
	  egg->id, this->id, this->x, this->y);
  write_graphic(server, buffer);
  fuel_player(server);
  write_iov(this, "ok\n");
  return (0);
}
