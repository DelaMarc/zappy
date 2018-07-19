/*
** graphic_cmd3.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:19:15 2016 Delaunay Marc
** Last update Sun Jun 26 18:06:03 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"

char	*graphic_get_players(t_server *server)
{
  char		buff[256];
  char		*str;
  t_client	*this;

  if (!server->clients->size ||
      (str = malloc(50 * server->clients->size)) == NULL)
    return (NULL);
  str[0] = '\0';
  FOREACH(t_pair *, tmp, server->clients)
    {
      this = ((t_client *)tmp->second);
      sprintf(buff, "pnw %zu %d %d %d %d %s\n", this->id, this->x, this->y,
	      GRAPHIC_DIR(this->dir), this->lvl, this->team->name);
      strcat(str, buff);
    }
  return (str);
}

char	*graphic_get_inventory(t_server *server)
{
  char		buff[256];
  char		*str;
  t_client	*t;

  if (!server->clients->size ||
      (str = malloc(50 * server->clients->size)) == NULL)
    return (NULL);
  str[0] = '\0';
  FOREACH(t_pair *, tmp, server->clients)
    {
      t = ((t_client *)tmp->second);
      sprintf(buff, "pin %zu %d %d %d %d %d %d %d %d %d\n", t->id, t->x,
	      t->y, t->inv[0], t->inv[1], t->inv[2], t->inv[3], t->inv[4],
	      t->inv[5], t->inv[6]);
      strcat(str, buff);
    }
  return (str);
}

char	*graphic_get_eggs(t_server *server)
{
  char	buff[256];
  char	*str;

  if ((str = malloc(1000)) == NULL)
    return (NULL);
  str[0] = '\0';
  FOREACH(t_team *, t, server->teams)
    {
      FOREACH(t_egg *, e, t->eggs)
	{
	  sprintf(buff, "enw %zu %d %d\n", e->id, e->x, e->y);
	  strcat(str, buff);
	}
    }
  return (str);
}

int	graphic_conn(t_server *server, t_client *this)
{
  char	*tmp[7];
  int	i;

  i = 0;
  tmp[0] = msz(server, NULL);
  tmp[1] = sgt(server, NULL);
  tmp[2] = mct(server, NULL);
  tmp[3] = tna(server, NULL);
  tmp[4] = graphic_get_players(server);
  tmp[5] = graphic_get_inventory(server);
  tmp[6] = graphic_get_eggs(server);
  while (i < 7)
    {
      if (tmp[i] && tmp[i][0] != '\0')
	write_iov(this, tmp[i]);
      free(tmp[i]);
      i++;
    }
  return (0);
}

void	graphic_pos(t_client *this, t_server *server)
{
  char	buffer[64];

  sprintf(buffer, "ppo %zu %d %d %d", this->id,
          this->x, this->y, GRAPHIC_DIR(this->dir));
  write_graphic(server, buffer);
}
