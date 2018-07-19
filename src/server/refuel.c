/*
** refuel.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Thu Jun 23 22:57:11 2016 Delaunay Marc
** Last update Sun Jun 26 03:33:25 2016 Louis Casamayou
*/

#include <sys/time.h>
#include "server.h"

void			refuel_eat(t_server *this)
{
  static struct timeval	last = {0, 0};
  struct timeval	now;
  int			i;
  int			qty;
  t_field		*tmp;
  static size_t		n = 0;

  gettimeofday(&now, NULL);
  if (!(last.tv_sec == now.tv_sec ?
  	last.tv_usec < now.tv_usec : last.tv_sec < now.tv_sec))
    return ;
  last = (struct timeval){now.tv_sec + (int)(126.0 / this->time),
  			  now.tv_usec
			  + ((int)((126.0 / this->time) * 1000000) % 1000000)};
  for (i = 0, qty = this->clients->size * 2; i < qty; ++i)
    {
      tmp = V2DGETP(t_field *, this->field,
		    rand() % this->y,
		    rand() % this->x);
      if (!tmp->stone[nourriture])
	++tmp->stone[nourriture];
      ++n;
    }
}

void	fuel_player(t_server *this)
{
  int	j;
  int	stone;

  for (stone = 0; stone < STONE_NBR; ++stone)
    {
      for (j = 0; j < 4; ++j)
	{
	  ++V2DGETP(t_field *, this->field,
		    rand() % this->y,
		    rand() % this->x)->stone[stone];
	}
    }
}

void    fuel_init(t_server *this)
{
  int	i;
  int	max;

  max = this->teams->size * this->clients_max;
  for (i = 0; i < max; ++i)
    {
      fuel_player(this);
    }
}
