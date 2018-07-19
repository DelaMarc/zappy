/*
** graphic_cmd.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:19:53 2016 Delaunay Marc
** Last update Sun Jun 26 18:02:35 2016 Louis Casamayou
*/

#include "foreach.h"
#include "server.h"

char	*mct(t_server *server, char *arg)
{
  char	buff[256];
  char	*str;

  (void)arg;
  if (!server->x || !server->y
      || (str = malloc(40 * server->x * server->y)) == NULL)
    return (NULL);
  str[0] = '\0';
  FOREACH(t_field *, f, server->field)
    {
      sprintf(buff, "bct %zu %zu %d %d %d %d %d %d %d\n", f->x, f->y,
	      f->stone[0], f->stone[1], f->stone[2], f->stone[3],
	      f->stone[4], f->stone[5], f->stone[6]);
      strcat(str, buff);
      if ((int)f->x == server->x - 1 && (int)f->y == server->y - 1)
	return (str);
    }
  return (str);
}

char	*suc(t_server *server, char *arg)
{
  (void)server;
  (void)arg;
  return (strdup("suc\n"));
}

char	*tna(t_server *server, char *arg)
{
  char	buff[256];
  char	*str;

  (void)arg;
  if (!server->teams->size || (str = malloc(50 * server->teams->size)) == NULL)
    return (NULL);
  str[0] = '\0';
  FOREACH(t_team *, t, server->teams)
    {
      sprintf(buff, "tna %s\n", t->name);
      strcat(str, buff);
    }
  return (str);
}

char	*bct(t_server *server, char *arg)
{
  char		*arg2;
  char		str[40];
  t_field	*f;

  arg2 = arg;
  while (*arg2 != ' ' && *arg2 != '\0')
    arg2++;
  if (*arg2 == '\0')
    return (NULL);
  *arg2 = '\0';
  arg2++;
  f = V2DGETP(t_field *, server->field, atoi(arg2), atoi(arg));
  sprintf(str, "bct %zu %zu %d %d %d %d %d %d %d\n", f->x, f->y,
	  f->stone[0], f->stone[1], f->stone[2], f->stone[3],
	  f->stone[4], f->stone[5], f->stone[6]);
  return (strdup(str));
}

char	*msz(t_server *server, char *arg)
{
  char	buff[256];

  (void)arg;
  sprintf(buff, "msz %d %d\n", server->x, server->y);
  return (strdup(buff));
}
