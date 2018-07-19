/*
** markov.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jun 23 18:47:15 2016 Loïc GIGOMAS
** Last update Sat Jun 25 21:45:11 2016 Loïc GIGOMAS
*/

#ifndef MARKOV_H_
# define MARKOV_H_

# include "new.h"
# include "vector.h"

# define MARKOV_FINISHED 1
# define MARKOV_CONTINUE 0

# define STATES_MAX	100

/*
** Init structures
*/
typedef struct	s_markov_node_init
{
  void		*data;
}		t_markov_node_init;

/*
** Link:
** child : index of the child node
** t_min/t_max : possibility tantiem (0<=x<1000) min/max
*/
typedef struct	s_markov_link_init
{
  size_t	child;
  size_t	t_min;
  size_t	t_max;
}		t_markov_link_init;

typedef struct	s_markov_init
{
  long int	seed;
  size_t	n_nodes;
  size_t	n_mandat;
}		t_markov_init;

/*
** Markov's structures
*/
typedef struct	s_markov_node
{
  t_object	__obj__;
  void		*data;
  t_vector	*links;
}		t_markov_node;

typedef struct	s_markov_link
{
  t_object	__obj__;
  size_t	node;
  size_t	t_min;
  size_t	t_max;
}		t_markov_link;

/*
** Actual is the index of the actual node
*/
typedef struct		s_markov
{
  t_object		__obj__;
  int			actual;
  t_vector		*nodes;
  t_vector		*mandat;
  struct drand48_data	dr48;
  size_t		step[STATES_MAX];
  void			(*init_state[STATES_MAX])(void *);
}			t_markov;

t_markov	*t_markov_new(t_markov_init var);
int		markov_mandat(t_markov *m, void *params);
t_markov_node	*markov_next(t_markov *m, void *p);

t_markov_link	*t_markov_link_new(t_markov_link_init var);

t_markov_node	*t_markov_node_new(t_markov_node_init var);

#endif /* !MARKOV_H_ */
