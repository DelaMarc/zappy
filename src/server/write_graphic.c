/*
** write_graphic.c for  in /home/delaun_m/clones/PSU_2015_zappy
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Thu Jun 23 14:55:21 2016 Delaunay Marc
** Last update Sun Jun 26 16:16:10 2016 Louis Casamayou
*/

#include "server.h"
#include "foreach.h"

int	graphic_dump_bct(t_server *server)
{
  int	alloc;
  char	*msg;
  char	buff[36];

  alloc = (server->field->sx * server->field->sy) * (35) + 2;
  if ((msg = malloc(alloc)) == NULL)
    return (1);
  msg[0] = '\0';
  FOREACH(t_field *, f, server->field)
    {
      sprintf(buff, "bct %zu %zu %d %d %d %d %d %d %d\n",
	      f->x, f->y, f->stone[0], f->stone[1],
	      f->stone[2], f->stone[3], f->stone[4],
	      f->stone[5], f->stone[6]);
      strcat(msg, buff);
    }
  write_graphic(server, msg);
  free(msg);
  return (0);
}

int		check_cmd_loop_graphics(t_server *s)
{
  size_t	i;
  t_client	*this;

  for (i = 0; i < s->graphics->size; ++i)
    {
      this = list_get(s->graphics, i);
      check_cmd_graphics(s, this);
    }
  return (0);
}

static int	remove_graphic_client(t_client *this, t_server *s, int i)
{
   char		*tmp;

   FD_CLR(this->fd, &s->writefds);
   FD_CLR(this->fd, &s->readfds);
   while ((tmp = CBGET(char *, this->precious)))
     free(tmp);
   list_remove(s->graphics, i);
   delete(this);
   return (0);
}

int		check_fd_graphics(t_server *s, fd_set *writefds, fd_set *readfds)
{
  size_t	i;
  t_client	*this;

  for (i = 0; i < s->graphics->size; ++i)
    {
      this = list_get(s->graphics, i);
      if (FD_ISSET(this->fd, readfds))
	{
	  if (read_client(this) == 1)
	    return (remove_graphic_client(this, s, i));
	}
      else if (this->iovcnt && FD_ISSET(this->fd, writefds) && iov_send(this))
	return (remove_graphic_client(this, s, i));
    }
  return (0);
}

void	write_graphic(t_server *server, char *msg)
{
  if (!server->graphics->size)
    return ;
  FOREACH(t_client *, this, server->graphics)
    {
      write_iov(this, msg);
    }
}
