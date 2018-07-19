/*
** egg.h for  in /home/delaun_m/clones/PSU_2015_zappy
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Thu Jun 23 16:16:34 2016 Delaunay Marc
** Last update Sat Jun 25 01:18:53 2016 Delaunay Marc
*/

#ifndef EGG_H_
# define EGG_H_

#include "timer.h"
#include "new.h"

typedef struct	s_team	t_team;
typedef struct	s_server	t_server;

typedef struct	s_egg_init
{
  t_client	*client;
  t_server	*s;
}		t_egg_init;

typedef struct	s_egg
{
  t_object      __obj__;
  t_team	*team;
  t_timer	*timer;
  int		ghost;
  int		x;
  int		y;
  size_t	id;
}		t_egg;

void	egg_del(void *s);
t_egg	*t_egg_new(t_egg_init var);

#include "server.h"
#include "team.h"

#endif /* EGG_H_ */
