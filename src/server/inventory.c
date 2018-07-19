/*
** inventory.c for zappy in /home/delaun_m/clones/PSU_2015_zappy/src/server
** 
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
** 
** Started on  Sun Jun 26 04:20:12 2016 Delaunay Marc
** Last update Sun Jun 26 04:20:13 2016 Delaunay Marc
*/

#include "server.h"

int     inventory_check(t_client *this, t_server *server, char *arg)
{
  int   val;

  if (arg)
    {
      free(arg);
      write_iov(this, "ko\n");
      return (1);
    }
  if ((val = commands_set_timer(this, server, TIME_INVENTORY)) == 0)
    return (1);
  else if (val == 1)
    {
      this->ptr_func = (void*)&inventory;
      return (1);
    }
  return (0);
}

int	inventory(t_client *this, t_server *server, char *arg)
{
  int	i;
  char	buf[128];
  char	minibuf[32];

  if (inventory_check(this, server, arg))
    return (0);
  i = 0;
  buf[0] = '\0';
  strcat(buf, "{");
  while (i < STONE_NBR)
    {
      if (i)
	sprintf(minibuf, ",%s %d", stoneName[i], this->inv[i]);
      else
	sprintf(minibuf, "%s %d", stoneName[i], this->inv[i]);
      strcat(buf, minibuf);
      i++;
    }
  strcat(buf, "}\n");
  write_iov(this, buf);
  return (0);
}
