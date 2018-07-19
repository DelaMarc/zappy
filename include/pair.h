/*
** pair.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 16:34:16 2016 Loïc GIGOMAS
** Last update Sat Jun 11 16:37:49 2016 Loïc GIGOMAS
*/

#ifndef PAIR_H_
# define PAIR_H_

# include "new.h"

typedef struct	s_pair_init
{
  void		*first;
  void		*second;
}		t_pair_init;

typedef struct	s_pair
{
  t_object	__obj__;
  void		*first;
  void		*second;
}		t_pair;

t_pair		*t_pair_new(t_pair_init var);

#endif /* !PAIR_H_ */
