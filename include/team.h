/*
** team.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jun 10 22:41:19 2016 Loïc GIGOMAS
** Last update Fri Jun 24 00:04:59 2016 Delaunay Marc
*/

#ifndef TEAM_H_
# define TEAM_H_

# include <stdlib.h>

# include <ctype.h>

#include "list.h"

/*
** new/delete
*/
# include "new.h"

# define TEAM_ARG	(-1)
# define TEAM_NOERR	(0)

/*
** t_map
*/
# include "map.h"

typedef struct	s_player	t_player;
typedef struct	s_egg		t_egg;

/*
** Tout les parametres doivent être définis avec maxConnexions > 0.
*/
typedef struct	s_team_init
{
  char		*name;
  size_t	maxConnexions;
}		t_team_init;

typedef struct	s_team
{
  t_object	__obj__;
  char		*name;
  t_map		*players;
  t_list	*eggs;
  size_t	maxConn;
  int		masters;
}		t_team;

/*
** team_modifiers.c
*/
t_team		*t_team_new(t_team_init var);
void		tea_del(void *ptr);
int		team_add_player(t_team *t, t_player *p);
int		team_remove_player(t_team *t, t_player *p);
int		team_set_maxConn(t_team *t, size_t mc);

/*
** team_accessors.c
*/
t_map		*team_players(t_team *t);
char		*team_name(t_team *t);
size_t		team_maxConn(t_team *t);

# include "player.h"
#include "egg.h"

void		manage_eggs(t_server *server);

#endif /* !TEAM_H_ */
