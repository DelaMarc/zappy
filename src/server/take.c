/*
** take.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:22:37 2016 Delaunay Marc
** Last update Sun Jun 26 15:38:53 2016 Louis Casamayou
*/

#include "server.h"

int     take_check(t_client *this, t_server *server, char *arg)
{
  int   val;

  if (!arg)
    {
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_TAKE)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&take;
      this->cmd_arg = arg;
      return (1);
    }
  return (0);
}

static int	graphic_take(t_client *this, t_server *server,
			     t_field *f, int i)
{
  char		buffer[256];
  char		tmp[256];

  buffer[0] = 0;
  sprintf(tmp, "pgt %zu %d\npin %zu %d %d %d %d %d %d %d %d %d\n",
	  this->id, i, this->id, this->x, this->y, this->inv[0],
	  this->inv[1], this->inv[2], this->inv[3], this->inv[4],
	  this->inv[5], this->inv[6]);
  strcat(buffer, tmp);
  sprintf(tmp, "bct %d %d %d %d %d %d %d %d %d\n", this->x, this->y,
	  f->stone[0], f->stone[1], f->stone[2], f->stone[3],
	  f->stone[4], f->stone[5], f->stone[6]);
  strcat(buffer, tmp);
  write_graphic(server, buffer);
  return (0);
}

int		take(t_client *this, t_server *server, char *arg)
{
  t_field	*f;
  int		i;

  if (take_check(this, server, arg))
    return (0);
  f = V2DGETP(t_field*, server->field, this->y, this->x);
  i = 0;
  while (i < STONE_NBR && strcasecmp(arg, stoneName[i]))
    i++;
  if (i == STONE_NBR || f->stone[i] == 0)
    {
      write_iov(this, "ko\n");
      return (0);
    }
  write_iov(this, "ok\n");
  f->stone[i]--;
  this->inv[i]++;
  return (graphic_take(this, server, f, i));
}
