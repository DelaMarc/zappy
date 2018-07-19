/*
** broadcast.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:17:33 2016 Delaunay Marc
** Last update Sun Jun 26 15:36:25 2016 Louis Casamayou
*/

#include <math.h>
#include "foreach.h"
#include "server.h"

int	broadcast_check(t_client *this, t_server *server, char *arg)
{
  int	val;

  if (!arg || strlen(arg) == 0)
    {
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_BROADCAST)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&broadcast;
      this->cmd_arg = arg;
      return (1);
    }
  return (0);
}

int		get_direction(double vec[2], double dir[2])
{
  double	angle;
  double	v;
  double	d;
  int		i;

  if (vec[0] == 0 && vec[1] == 0)
    return (0);
  v = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
  d = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
  vec[0] /= v;
  vec[1] /= v;
  dir[0] /= d;
  dir[1] /= d;
  angle = acos((vec[0] * dir[0] + vec[1] * dir[1]));
  if (vec[0] * dir[1] - vec[1] * dir[0] > 0)
    angle =  2 * M_PI - angle;
  angle = (angle * 180.0) / M_PI;
  i = 0;
  while (i < 7)
    {
      if (angle > 22.5 + 45 * i && angle <= 67.5 + 45 * i)
	return (i + 2);
      i++;
    }
  return (1);
}

static int	graphic_broadcast(t_client *this, t_server *server, char *arg)
{
  char	*str;

  if ((str = malloc(strlen(arg) + 16)) == NULL)
    return (1);
  sprintf(str, "pbc %zu %s\n", this->id, arg);
  write_graphic(server, str);
  free(str);
  return (0);
}

int		broadcast(t_client *this, t_server *server, char *arg)
{
  double	vec[2];
  double	dir[2];
  t_client	*dest;
  char		buf[512];

  if (broadcast_check(this, server, arg))
    return (0);
  if (graphic_broadcast(this, server, arg))
    return (3);
  FOREACH(t_pair *, tmp, server->clients)
    {
      dest = ((t_client *)tmp->second);
      if (dest->fd != this->fd)
	{
	  vec[0] = M((this->x - dest->x), server->x / 2.0);
	  vec[1] = M((this->y - dest->y), server->y / 2.0);
	  dir[0] = ((dest->dir + 1) & 1) * (1 - (dest->dir & 2));
	  dir[1] = (dest->dir & 1) * (1 - (dest->dir & 2));
	  sprintf(buf, "message %d,%s\n", get_direction(vec, dir), arg);
	  write_iov(dest, buf);
	}
      else
	write_iov(dest, "ok\n");
    }
  return (0);
}
