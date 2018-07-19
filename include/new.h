/*
** new.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jun 10 21:13:43 2016 Loïc GIGOMAS
** Last update Sat Jun 11 00:33:19 2016 Loïc GIGOMAS
*/

#ifndef NEW_H_
# define NEW_H_

/*
** Warning inutile, la norme de compilation exige que les champs
** non explicitement initialisés soient mis à 0. Norme que GCC respecte.
*/
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"

# include <stdlib.h>

typedef void	(*del_func)(void *ptr);

typedef struct	s_object_init
{
  size_t	obj_size;
  del_func	del;
}		t_object_init;

typedef struct	s_object	t_object;

struct		s_object
{
  t_object	*next;
  t_object	*prev;
  del_func	__delete__;
};

t_object	*t_object_new(t_object_init var);
void		_delete(t_object *obj);
void		_reg_object(t_object *obj);
void		_unreg_object(t_object *obj);

# define new(type, ...) (type##_new((type##_init){__VA_ARGS__}))

# define delete(var) _delete((t_object *)var)

#endif /* !NEW_H_ */
