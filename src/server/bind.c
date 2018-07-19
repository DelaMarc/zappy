/*
** bind.c for zappy in /home/monder_s/PSU_2015_zappy/src
**
** Made by Sacha Sacha Monderer
** Login   <monder_s@epitech.net>
**
** Started on  Wed Jun  8 14:22:23 2016 Sacha Sacha Monderer
** Last update Sun Jun 26 03:54:20 2016 Louis Casamayou
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"

static int	my_bind(t_server* server, struct sockaddr_in s_in_server)
{
  if (bind(server->fd,
	   (const struct sockaddr *)&s_in_server,
	   sizeof(s_in_server)) == -1) {
    perror("bind");
    return (1);
  }
  return (0);
}

static int	my_setsockopt(t_server *this)
{
  int	optval;

  optval = 1;
  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEPORT, &optval,
		 sizeof(optval)) == -1)
    {
      perror("setsockopt");
      return (1);
    }
  return (0);
}

int			launch_server(t_server *this)
{
  struct sockaddr_in	s_in_server;
  struct protoent	*pe;

  pe = getprotobyname("TCP");
  if (pe)
    {
      s_in_server.sin_family = AF_INET;
      s_in_server.sin_port = htons(this->port);
      s_in_server.sin_addr.s_addr = INADDR_ANY;
      if (((this->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) != -1) &&
	  my_bind(this, s_in_server) == 0 &&
	  listen(this->fd, 20) == 0)
	return (my_setsockopt(this));
      else
	{
	  if (this->fd == -1)
	    perror("socket");
	  close(this->fd);
	  return (1);
	}
    }
  perror("getprotobyname");
  return (1);
}
