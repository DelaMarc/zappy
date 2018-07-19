/*
** client.h for  in /home/delaun_m/clones/PSU_2015_zappy/src/server
**
** Made by Delaunay Marc
** Login   <delaun_m@epitech.net>
**
** Started on  Wed Jun  8 17:30:19 2016 Delaunay Marc
** Last update Sun Jun 26 17:51:44 2016 Louis Casamayou
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/uio.h>
# include "new.h"
# include "circularBuff.h"
# include "timer.h"
# include "team.h"
# include "stones.h"

# define LIFE_UNIT	(126)
# define M(a, b) (a < 0 ? (a < -b ? a + b * 2 : a) : (a > b ? a - b * 2 : a))
# define GRAPHIC_DIR(dir) (dir == 2 ? 4 : (6 - dir) % 4)

typedef struct	s_server	t_server;

typedef	struct	s_client_init
{
  t_server	*s;
}		t_client_init;

typedef enum	e_client_mask
  {
    from_egg = 1,
    ghost = 2,
    graphic = 4
  }		t_client_mask;

typedef struct		s_client
{
  t_object	__obj__;
  int			fd;
  int			x;
  int			y;
  int			dir;
  int			lvl;
  int			inv[STONE_NBR];
  struct iovec		io[10];
  int			iovcnt;
  char			*read_tmp;
  int			read_size;

  int(*ptr_func)(struct s_client*, void*, char*);

  t_circularBuff	*precious;
  char			*cmd_arg;

  t_timer		*timer;
  t_timer		*life;

  t_team		*team;
  int			mask;
  size_t		id;
}			t_client;

void		cli_del(void *s);
t_client       	*t_client_new(t_client_init var);
int		client_cmp(const void *a, const void *b);

int	set_client_fd(void *e,  void *oldfd, void *n);
int	get_client_fd(void *e, void *oldfd, void *n);
int	check_client_fd(void *e, void *server, void *n);
int	read_client(t_client *this);
void	write_iov(t_client *this, char *msg);
int     iov_send(t_client *this);
int	get_next_line(t_client *c, char **ret);
void	graphic_pos(t_client *this, t_server *server);
void	write_graphic(t_server *server, char *msg);

# include "server.h"

#endif /* !CLIENT_H_ */
