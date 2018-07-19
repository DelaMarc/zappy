/*
** foreach.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 17:34:06 2016 Loïc GIGOMAS
** Last update Wed Jun 22 15:50:38 2016 Loïc GIGOMAS
*/

#ifndef FOREACH_H_
# define FOREACH_H_

# include "new.h"

/*
** To correctly work with foreach, the container must be in the form :
** struct s_<container>
** {
**   t_object	__obj__;
**   size_t	nElemsInArray;
**   void	**arrayOfElements;
**   ...
** };
*/

/*
** Utilities for the FOREACH macro
*/
# define FIRST(c) (*(void ***)((void *)c + sizeof(t_object) + sizeof(size_t)))
# define LAST(c) (FIRST(c) + *((size_t *)(((void *)c) + sizeof(t_object))))

# define FE_INIT(t, e, c) void **_cur_ = FIRST(c); for (t e = (t)*_cur_
# define FE_COND(t, e, c) _cur_ != LAST(c)
# define FE_END(t, e) e = (t)*(++_cur_))

# define FOREACH(t, e, c) FE_INIT(t, e, c); FE_COND(t, e, c); FE_END(t, e)

#endif /* !FOREACH_H_ */
