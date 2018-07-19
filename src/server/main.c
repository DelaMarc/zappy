/*
** main.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Sun Jun 26 04:20:26 2016 Delaunay Marc
** Last update Sun Jun 26 23:35:39 2016 Loïc GIGOMAS
*/

#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include "lambda.h"
#include "server.h"

int main(int ac, char **av)
{
  t_server	*server;
  void		(*f_endrun)(int sig);

  f_endrun = FUNCTION(void, (int sig),
		      {
			(void) sig;
			if (server)
			  server->run = 0;
		      });
  signal(SIGINT, f_endrun);
  signal(SIGUSR1, f_endrun);
  signal(SIGQUIT, f_endrun);
  if ((server = new(t_server, ac, av)) == NULL)
    {
      fprintf(stderr, "Erreur à la création du serveur (%s).\n",
	      (errno ? strerror(errno) : "params"));
      return (1);
    }
  if (server->teams->size < 2)
    return (printf("%s%s%s", USAGE1, USAGE2, USAGE3));
  fuel_init(server);
  printf("server running\nport: %d\n", server->port);
  server_loop(server);
  delete(server);
  return (0);
}
