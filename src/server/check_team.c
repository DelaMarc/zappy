/*
** check_team.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Wed Jun 22 15:47:48 2016 Delaunay Marc
** Last update Sun Jun 26 15:36:44 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"

static int	graphic_client(t_client *this, t_server *server)
{
  map_remove(V2DGETP(t_field *, server->field, this->y, this->x)->players,
	     &this->fd);
  map_remove(server->clients, &this->fd);
  list_add(server->graphics, this, 0);
  this->mask = this->mask | graphic;
  graphic_conn(server, this);
  return (2);
}

static int	check_team_ko(t_client *this)
{
  write_iov(this, "ko\n");
  iov_send(this);
  return (1);
}

static t_client	*eclosion(t_client *this, t_server *server)
{
  char	buffer[64];
  t_egg	*egg;

  --this->team->maxConn;
  if (this->team->eggs->size)
    {
      egg = (t_egg *)list_get(this->team->eggs, 0);
      if (egg->ghost)
	{
	  move_player_to(server, this, egg->x, egg->y);
	  sprintf(buffer, "ebo %zu\npnw %zu %d %d %d %d %s\n",
		  egg->id, this->id, this->x, this->y, GRAPHIC_DIR(this->dir),
		  this->lvl, this->team->name);
	  write_graphic(server, buffer);
	  sprintf(buffer, "ebo %zu\n", egg->id);
	  write_graphic(server, buffer);
	  this->mask = this->mask | from_egg;
	  list_remove(this->team->eggs, 0);
	}
    }
  return (this);
}

static void	check_team_graphic(t_server *s, t_client *player)
{
  char	buffer[64];

  sprintf(buffer, "pnw %zu %d %d %d %d %s\n",
	  player->id, player->x, player->y, GRAPHIC_DIR(player->dir),
	  player->lvl, player->team->name);
  write_graphic(s, buffer);
}

int	check_team(t_client *this, t_server *server, char *cmd)
{
  char	buf[128];

  if (!strcmp(cmd, "GRAPHIC"))
    return (graphic_client(this, server));
  FOREACH(t_team *, tmp, server->teams)
    {
      if (!strcmp(cmd, tmp->name))
        {
          this->team = tmp;
	  if (tmp->maxConn)
	    eclosion(this, server);
	  else
	    return (check_team_ko(this));
          sprintf(buf, "%d\n%d %d\n", (int)tmp->maxConn, server->x, server->y);
          write_iov(this, buf);
	  check_team_graphic(server, this);
          return (2);
        }
    }
  return (check_team_ko(this));
}
