/*
** timer.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jun 14 18:05:41 2016 Loïc GIGOMAS
** Last update Wed Jun 22 18:03:11 2016 Louis Casamayou
*/

#ifndef TIMER_H_
# define TIMER_H_

# include "new.h"

# define TIMER_FUNC	(-2)
# define TIMER_ARGS	(-1)
# define TIMER_END	(1)
# define TIMER_RUN	(0)
# define TIME_LEFT	(7)
# define TIME_RIGHT	(7)
# define TIME_WALK	(7)
# define TIME_SEE	(7)
# define TIME_INVENTORY (1)
# define TIME_TAKE	(7)
# define TIME_SET	(7)
# define TIME_EVICT	(7)
# define TIME_BROADCAST	(7)
# define TIME_INCANTATION (300)
# define TIME_EGG_FORK	(42)
# define TIME_CONNECT_NBR (0)

/*
** Convertir des secondes en microsecondes
*/
# define MICSEC(n) ((n) * 1000000.0)

/*
** Convertir et recuperer le temps en fonction de t
*/
# define TTIME(n, t) ((size_t)MICSEC(((double)(n) / (double)(t))))

/*
** time : le temps d'attente en microsecondes.
*/
typedef struct	s_timer_init
{
  size_t	time;
}		t_timer_init;

typedef struct	s_timer
{
  t_object	__obj__;
  long int	seconds;
  long int	micros;
}		t_timer;

t_timer		*t_timer_new(t_timer_init var);
int		timer_finished(t_timer *t);
int		set_timer(t_timer *t, size_t n);
int		add_timer(t_timer *t, size_t n);

#endif /* !TIMER_H_ */
