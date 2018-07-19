/*
** server.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:21:55 2016 Delaunay Marc
** Last update Sun Jun 26 04:21:57 2016 Delaunay Marc
*/

#include <time.h>
#include <getopt.h>
#include <strings.h>
#include "server.h"
#include "list.h"

static void	*assign_commands_graph(t_server *this)
{
  if ((this->command_graph_map = new(t_map, &my_strcasecmp, 9,
                                     &suc)) == NULL)
    return (NULL);
  if (map_add(this->command_graph_map, "msz", &msz) != MAP_NOERR ||
      map_add(this->command_graph_map, "bct", &bct) != MAP_NOERR ||
      map_add(this->command_graph_map, "mct", &mct) != MAP_NOERR ||
      map_add(this->command_graph_map, "tna", &tna) != MAP_NOERR ||
      map_add(this->command_graph_map, "ppo", &ppo) != MAP_NOERR ||
      map_add(this->command_graph_map, "plv", &plv) != MAP_NOERR ||
      map_add(this->command_graph_map, "pin", &pin) != MAP_NOERR ||
      map_add(this->command_graph_map, "sgt", &sgt) != MAP_NOERR ||
      map_add(this->command_graph_map, "sst", &sst) != MAP_NOERR)
    return (NULL);
  return (this);
}

static	void	*assign_commands(t_server *this)
{
  if ((this->command_map = new(t_map, &my_strcasecmp, 12, &player_afk))
      == NULL)
    return (NULL);
  if (map_add(this->command_map, "avance", &walk) != MAP_NOERR ||
      map_add(this->command_map, "droite", &right) != MAP_NOERR ||
      map_add(this->command_map, "gauche", &left) != MAP_NOERR ||
      map_add(this->command_map, "voir", &see) != MAP_NOERR ||
      map_add(this->command_map, "inventaire", &inventory) != MAP_NOERR ||
      map_add(this->command_map, "prend", &take) != MAP_NOERR ||
      map_add(this->command_map, "pose", &set) != MAP_NOERR ||
      map_add(this->command_map, "expulse", &evict) != MAP_NOERR ||
      map_add(this->command_map, "broadcast", &broadcast) != MAP_NOERR ||
      map_add(this->command_map, "incantation", &incantation) != MAP_NOERR ||
      map_add(this->command_map, "fork", &egg_fork) != MAP_NOERR ||
      map_add(this->command_map, "connect_nbr", &connect_nbr))
    return (NULL);
  return (assign_commands_graph(this));
}

static	void	*init_server(t_server *this)
{
  this->port = 4242;
  this->x = 10;
  this->y = 10;
  this->clients_max = 10;
  this->time = 100;
  if ((this->parse_map = new(t_map, &varcmp, 6, &afk)) == NULL)
    return (NULL);
  this->port = 4242;
  if (map_add(this->parse_map, "p", &getPort) != MAP_NOERR ||
      map_add(this->parse_map, "x", &getX) != MAP_NOERR ||
      map_add(this->parse_map, "y", &getY) != MAP_NOERR ||
      map_add(this->parse_map, "n", &getTeams) != MAP_NOERR ||
      map_add(this->parse_map, "c", &getNbc) != MAP_NOERR ||
      map_add(this->parse_map, "t", &getT))
    return (NULL);

  if ((this->teams = new(t_vector)) == NULL)
    return (NULL);
  return (assign_commands(this));
}

static	t_server	*t_server_assign(t_server *new)
{
  int			i;
  int			j;

  if ((new->graphics = new(t_list, 1)) == NULL)
    return (NULL);
  if ((new->clients = new(t_map, &intcmp)) == NULL)
    return (NULL);
  if ((new->field = new(t_vector2d, new->y, new->x)) == NULL)
    return (NULL);
  for (i = 0; i < new->y; ++i)
    {
      for (j = 0; j < new->x; ++j)
	{
	  V2DSETP(new->field, i, j, new(t_field, i, j));
	}
    }
  for (i = 0; (size_t)i < new->teams->size; ++i)
    VGETP(t_team *, new->teams, i)->maxConn = new->clients_max;
  if (launch_server(new))
    return (NULL);
  return (new);
}

t_server	*t_server_new(t_server_init var)
{
  t_server	*new;
  int		opt;

  if (!var.ac || !var.av)
    return (NULL);
  if ((new = (t_server *)new(t_object, sizeof(t_server), &ser_del)) == NULL)
    return (NULL);
  if ((new = init_server(new)) == NULL)
    return (NULL);
  while ((opt = getopt(var.ac, var.av, "p:x:y:n:c:t:")) != -1)
    {
      if (opt == '?' || opt == ':')
	return (NULL);
      else
	{
	  optind--;
	  MGET(t_parse_f, new->parse_map, &opt)(new, var.av);
	}
    }
  srand(time(NULL));
  new->run = 1;
  return (t_server_assign(new));
}
