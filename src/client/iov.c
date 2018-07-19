/*
** iov.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jun 23 22:45:06 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:29:33 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include "client/client.h"

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
