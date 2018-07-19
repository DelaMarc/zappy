/*
** client.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/src
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 18 17:33:36 2016 Loïc GIGOMAS
** Last update Sat Jun 25 06:52:50 2016 Loïc GIGOMAS
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "new.h"

# include "stones.h"

# include "circularBuff.h"

# include "client/markov.h"

# include <sys/uio.h>

typedef	struct	s_client_init
{
  int		ac;
  char		**av;
}		t_client_init;

typedef struct		s_client
{
  t_object		__obj__;
  int			fd;
  int			verbose;
  int			x;
  int			y;
  int			dir;
  int			lvl;
  int			slot;
  int			sight[81][8];
  int			inv[STONE_NBR];

  fd_set		readfds;
  fd_set		writefds;
  int			run;

  struct iovec		io[10];
  int			iovcnt;

  char			*read_tmp;
  int			read_size;
  int			last_gnl;

  char			*team;
  char			*host;
  int			port;

  t_markov		*markov;
  t_circularBuff	*received;
}			t_client;

void		cli_del(void *s);
t_client       	*t_client_new(t_client_init var);
int		client_send(t_client *c, char *data);
int		client_recv(t_client *c, char **data);
int		get_next_line(t_client *c, int fd, char **ret);

void		write_iov(t_client *this, char *msg);
int		iov_send(t_client *this);

int		client_loop(t_client *this);

int		command_avance(t_client *this);
int		command_droite(t_client *this);
int		command_gauche(t_client *this);

int		command_voir(t_client *this);
int		command_inventaire(t_client *this);
int		command_prendre(t_client *this, char *obj);
int		command_poser(t_client *this, char *obj);

int		command_expulse(t_client *this);
int		command_broadcast(t_client *this, char *msg);
int		command_incantation(t_client *this);
int		command_fork(t_client *this);
int		command_slot(t_client *this);

void		parse_inventaire(t_client *, char *);
void		parse_voir(t_client *, char *);

int		vision_depth(int);
void		clear_state(int *);
void		update_row(int *, char *);
int		update_sight(int *, char *);
void		update_rows(t_client *, char *, int);

#endif /* !CLIENT_H_ */
