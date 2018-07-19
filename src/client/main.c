/*
** main.c for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 25 22:30:16 2016 Loïc GIGOMAS
** Last update Sat Jun 25 22:30:17 2016 Loïc GIGOMAS
*/

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "lambda.h"
#include "client/client.h"
#include "client/ai.h"

int main(int ac, char **av)
{
  t_client	*c;
  void		(*f_endrun)(int sig);

  f_endrun = FUNCTION(void, (__attribute__((unused))int sig),
		      {
			write(1, "Fermeture demandee\n", 19);
			if (c)
			  c->run = 0;
		      });
  signal(SIGINT, f_endrun);
  signal(SIGUSR1, f_endrun);
  signal(SIGQUIT, f_endrun);
  if ((c = new(t_client, ac, av)) == NULL || !set_ai(c) || !c->team)
    {
      write(2, "Initialisation or argument error.\n", 34);
      if (errno)
	perror(NULL);
      return (1);
    }
  client_loop(c);
  delete(c);
  return (0);
}
