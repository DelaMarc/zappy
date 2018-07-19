/*
** check_cmd.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:09:48 2016 Delaunay Marc
** Last update Sun Jun 26 04:17:44 2016 Delaunay Marc
*/

#include "server.h"
#include "foreach.h"

char	*get_arg(char *cmd)
{
  int	i;

  i = 0;
  while (cmd[i] != '\0' && cmd[i] != ' ')
    i++;
  if (cmd[i] == '\0')
    return (NULL);
  cmd[i] = '\0';
  return (strdup(cmd + i + 1));
}

int	check_cmd_graphics(t_server *server, t_client *client)
{
  char	*(*ptr)(t_server *, char *);
  char	*cmd;
  char	*arg;
  char	*str;

  if ((cmd = CBGET(char *, client->precious)) == NULL)
    return (0);
  arg = get_arg(cmd);
  ptr = map_get(server->command_graph_map, cmd);
  str = ptr(server, arg);
  if (str == NULL)
    return (3);
  write_iov(client, str);
  free(str);
  free(cmd);
  free(arg);
  return (0);
}

static int	check_cmd_step2(t_server *server, t_client *client,
				char *cmd, char *arg)
{
  int		r;
  int	(*ptr)(t_client *, t_server *, char *);

  if ((cmd = CBGET(char *, client->precious)) == NULL)
    return (0);
  if (client->team == NULL)
    {
      r = check_team(client, server, cmd);
      free(cmd);
      return (r);
    }
  arg = get_arg(cmd);
  ptr = map_get(server->command_map, cmd);
  ptr(client, server, arg);
  free(cmd);
  return (0);
}

int	check_cmd(t_server *server, t_client *client)
{
  char	*cmd;
  char	*arg;

  cmd = NULL;
  arg = NULL;
  if (kill_player(client, server))
    return (1);
  if (client->mask & ghost || client->mask & graphic
      || timer_finished(client->timer) == TIMER_RUN)
    return (0);
  else if (client->ptr_func)
    {
      client->ptr_func(client, server, client->cmd_arg);
      client->ptr_func = NULL;
      free(client->cmd_arg);
      client->cmd_arg = NULL;
    }
  return (check_cmd_step2(server, client, cmd, arg));
}
