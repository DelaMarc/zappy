/*
** player.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jun 10 22:35:05 2016 Loïc GIGOMAS
** Last update Mon Jun 20 16:20:15 2016 Sacha Sacha Monderer
*/

#ifndef PLAYER_H_
# define PLAYER_H_

# include <stdlib.h>

/*
** new/delete
*/
# include "new.h"

/*
** client, stones, teams, map field
*/
# include "client.h"
# include "stones.h"

typedef struct	s_team	t_team;
typedef struct	s_field	t_field;
typedef struct  s_client t_client;

/*
** Ces elements ne peuvent être null.
*/
typedef struct	s_player_init
{
  t_team	*team;
  t_field	*field;
  t_client	*client;
}		t_player_init;

typedef struct	s_player
{
  t_object	__obj__;
  __uint16_t	stone[STONE_NBR];
  t_team	*team;
  t_field	*field;
  t_client	*client;
}		t_player;

/*
** player_modifiers.c
*/
t_player	*t_player_new(t_player_init var);
void		player_addStone(t_player *p, t_stoneType t);
void		player_remStone(t_player *p, t_stoneType t);

/*
** player_accessors.c
*/
t_team		*player_team(t_player *p);
t_field		*player_field(t_player *p);
__uint16_t	player_getStone(t_player *p, t_stoneType t);

# include "field.h"
# include "team.h"

#endif /* !PLAYER_H_ */
