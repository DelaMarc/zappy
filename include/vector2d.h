/*
** vector2d.h for Zappy in /home/gigoma_l/rendu/PSU_2015_myirc
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sun Jun  5 08:25:49 2016 Loïc GIGOMAS
** Last update Sun Jun 26 23:17:51 2016 Loïc GIGOMAS
*/

#ifndef VECTOR2D_H_
# define VECTOR2D_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** memset
*/
# include <string.h>

/*
** new/delete
** vector herited functions
*/
# include "new.h"
# include "vector.h"

# define V (t_vector *)
# define V2DGET(t, v, iy, ix) (*(t *)vector_at(V v, (iy) * (v)->sx + (ix)))
# define V2DGETP(t, v, iy, ix) ((t)vector_at(V v, (iy) * (v)->sx + (ix)))
# define V2DSET(t, v, iy, ix, e) (V2DGET(t, V v, ix, iy) = (e))
# define V2DSETP(v, y, ix, e) (vector_set(V v, (y)*(v)->sx+(ix), (void *)(e)))
# undef v

/*
** Enum pour les modifiers
*/
typedef enum
{
  UNDEF,
  COL,
  ROW
}	t_2dType;

/*
** Utilisé pour le new (initialisation).
*/
typedef struct	s_vector2d_init
{
  size_t	sizex;
  size_t	sizey;
}		t_vector2d_init;

/*
** Contiens le t_vector (pour "l'héritage")
** Seul 1 t_vector sera utilisé pour le gain de place
*/
typedef struct	s_vector2d
{
  t_vector	_v;
  size_t	sx;
  size_t	sy;
}		t_vector2d;

/*
** vector2d_modifiers.c
*/
t_vector2d	*t_vector2d_new(t_vector2d_init var);
void		vec2d_del(void *v);
int		vector2d_push(t_vector2d *v, t_2dType type);
int		vector2d_pop(t_vector2d *v, t_2dType type);

/*
** vector2d_accessors.c
*/
size_t		vector2d_size(t_vector2d *v);
size_t		vector2d_alloc(t_vector2d *v);
size_t		vector2d_sizeX(t_vector2d *v);
size_t		vector2d_sizeY(t_vector2d *v);

#endif /* !VECTOR2D_H_ */
