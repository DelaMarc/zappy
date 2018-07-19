/*
** client.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:29:44 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:35:21 2016 Loïc GIGOMAS
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "client/client.h"

void		cli_del(void *s)
{
  t_client	*this;

  this = (t_client *)s;
  if (this->fd)
    {
      printf("Closing connection.\n");
      close(this->fd);
    }
}

t_client		*t_client_connect(t_client *this)
{
  struct sockaddr_in    in_client;
  struct protoent	*pe;
  struct hostent	*he;

  printf("Connection to host %s:%d.\n", this->host, this->port);
  if (!(pe = getprotobyname("TCP")) || !(he = gethostbyname(this->host)))
    return (NULL);
  in_client.sin_family = AF_INET;
  in_client.sin_port = htons(this->port);
  if ((this->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (NULL);
  bcopy((char *)he->h_addr, (char *)&in_client.sin_addr.s_addr, he->h_length);
  if (connect(this->fd, (struct sockaddr *)&in_client,
	      sizeof(in_client)) == -1)
    return (NULL);
  this->lvl = 1;
  this->run = 1;
  return (this);
}

int	client_flags(t_client *this, char **arg, int opt)
{
  if (opt == 'n')
    this->team = arg[optind];
  else if (opt == 'p')
    {
      if ((this->port = atoi(arg[optind])) == -1)
	return (1);
    }
  else
      this->host = arg[optind];
  return (0);
}

t_client	*t_client_new(t_client_init var)
{
  int		opt;
  t_client	*new;

  if (!var.ac || !var.av)
    return (NULL);
  if ((new = (t_client *)new(t_object, sizeof(t_client), &cli_del)) == NULL)
    return (NULL);
  if ((new->markov = new(t_markov)) == NULL ||
      (new->received = new(t_circularBuff, 20)) == NULL)
    return (NULL);
  new->team = NULL;
  new->host = "localhost";
  new->port = 4242;
  while ((opt = getopt(var.ac, var.av, "n:p:h:")) != -1)
    {
      if (opt == '?' || opt == ':')
        return (NULL);
      else
	{
	  --optind;
	  if (client_flags(new, var.av, opt))
	    return (NULL);
	}
    }
  return (t_client_connect(new));
}
