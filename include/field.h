/*
** field.h for Zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Wed Jun  8 17:31:52 2016 Delaunay Marc
** Last update Thu Jun 23 18:59:50 2016 Louis Casamayou
*/

#ifndef FIELD_H_
# define FIELD_H_

# include <ctype.h>

/*
** new/delete
*/
# include "new.h"
# include "stones.h"
# include "client.h"
# include "map.h"

# define FIELD_ARGS	(0)
# define FIELD_NOERR	(0)

typedef struct	s_field_init
{
  size_t	y;
  size_t	x;
}		t_field_init;

typedef struct	s_field	t_field;

struct	s_field
{
  t_object	__obj__;
  size_t	y;
  size_t	x;
  __uint16_t	stone[STONE_NBR];
  t_map		*players;
  t_field	*adjacent[4];
};

/*
** field_modifiers.c
*/
t_field		*t_field_new(t_field_init var);
void		fie_del(void *ptr);
int		field_adjacents(t_field *f, t_field *adj[4]);

/*
** field_accessors.c
*/

/* LA DIRECTION (INT) SERA A CHANGER PAR LE DEFINE/L'ENUM CORRESPONDANT */
t_field		*field_size(t_field *f, int direction);

#endif /* FIELD_H_ */
