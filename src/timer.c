/*
** timer.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:30:49 2016 Loïc GIGOMAS
** Last update Sun Jun 26 17:31:02 2016 Louis Casamayou
*/

#include <sys/time.h>
#include "timer.h"

t_timer			*t_timer_new(t_timer_init var)
{
  struct timeval	tv;
  t_timer		*t;

  if (gettimeofday(&tv, NULL) == -1)
    return (NULL);
  if ((t = (t_timer *)new(t_object, sizeof(t_timer))) == NULL)
    return (NULL);
  t->micros = tv.tv_usec + (var.time % 1000000);
  t->seconds = tv.tv_sec + (var.time / 1000000);
  if (t->micros >= 1000000)
    {
      t->seconds++;
      t->micros -= 1000000;
    }
  return (t);
}

int			timer_finished(t_timer *t)
{
  struct timeval	tv;

  if (!t)
    return (TIMER_ARGS);
  if (gettimeofday(&tv, NULL) == -1)
    return (TIMER_FUNC);
  if ((t->seconds == tv.tv_sec ?
       t->micros < tv.tv_usec : t->seconds < tv.tv_sec))
    return (TIMER_END);
  return (TIMER_RUN);
}

int			set_timer(t_timer *t, size_t n)
{
  struct timeval	tv;

  if (!t)
    return (TIMER_ARGS);
  if (gettimeofday(&tv, NULL) == -1)
    return (TIMER_FUNC);
  t->seconds = tv.tv_sec + (n / 1000000);
  t->micros = tv.tv_usec + (n % 1000000);
  if (t->micros >= 1000000)
    {
      t->seconds++;
      t->micros -= 1000000;
    }
  return (1);
}

int			add_timer(t_timer *t, size_t n)
{
  if (!t)
    return (TIMER_ARGS);
  t->seconds += (n / 1000000);
  t->micros += (n % 1000000);
  if (t->micros >= 1000000)
    {
      t->seconds++;
      t->micros -= 1000000;
    }
  return (1);
}
