/*
** iov.c for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Mon Jun 20 15:57:27 2016 Delaunay Marc
** Last update Sun Jun 26 16:46:57 2016 Louis Casamayou
*/

#include "client.h"

void		write_iov(t_client *this, char *msg)
{
  size_t	len;
  char		*m;

  len = strlen(msg);
  if (len == 0)
    ++len;
  m = malloc(len + (msg[len - 1] == '\n' ? 1 : 2));
  m = strcpy(m, msg);
  if (m[len - 1] != '\n')
    {
      m = strcat(m, "\n");
      ++len;
    }
  this->io[this->iovcnt].iov_base = m;
  this->io[this->iovcnt].iov_len = len;
  ++this->iovcnt;
}

int	iov_send(t_client *this)
{
  int	i;

  if (writev(this->fd, this->io, this->iovcnt) == -1)
    {
      perror("writev");
      return (1);
    }
  for (i = 0; i < this->iovcnt; ++i)
    {
      free(this->io[i].iov_base);
    }
  this->iovcnt = 0;
  return (0);
}
