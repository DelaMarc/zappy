/*
** server.h for  in /home/casama_l/PSU_2015_zappy/include
**
** Made by Louis Casamayou
** Login   <casama_l@epitech.net>
**
** Started on  Sun Jun 26 04:28:12 2016 Louis Casamayou
** Last update Sun Jun 26 23:39:41 2016 Loïc GIGOMAS
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/select.h>

# include "new.h"
# include "vector.h"
# include "vector2d.h"
# include "map.h"
# include "field.h"
# include "team.h"
# include "field.h"
# include "list.h"

# define TRIPOSX(r, c, d, s)	((r * (1 - (2 * (d & 1))) + c * (d & 1)) * s)
# define TRIPOSY(r, c, d, s)	((c * ((d + 1) & 1) - r) * s)
# define MOD(a, b)		(a % (int)b < 0 ? (a % (int)b) + b : a % b)
# define USAGE1 "Usage: 2 teams needed at least (use -n team_name ...)"
# define USAGE2 " [-p port -x lenght -y height -c max_connexions -t time]\n"
# define USAGE3 " With 3 < (X || Y) <= 100 and 1 <= t <= 1000"

typedef struct	s_client	t_client;

typedef struct	s_server_init
{
  int		ac;
  char		**av;
}		t_server_init;

/* caractères à parser: pxynct */
typedef	struct	s_server
{
  t_object	__obj__;
  int		run;
  int		fd;
  int		port;
  int		x;
  int		y;
  int		clients_max;
  double	time;
  int		max_fd;
  fd_set	readfds;
  fd_set	writefds;

  t_map		*command_map;
  t_map		*command_graph_map;
  t_map		*parse_map;
  t_map		*clients;
  t_vector	*teams;
  char		*winner;
  /* graphic client doesn't die, just receives datas  */
  t_list	*graphics;
  t_vector2d	*field;
}		t_server;

/* pointeur sur fonction du parser de server */
typedef int (*t_parse_f)(t_server *, char**);

int	varcmp(const void *s1, const void *s2);
int	intcmp(const void *a, const void *b);
int	getTeams(t_server *s, char **arg);
int	getPort(t_server *s, char **arg);
int	getNbc(t_server *s, char **arg);
int	getT(t_server *s, char **arg);
int	getX(t_server *s, char **arg);
int	getY(t_server *s, char **arg);
int	afk(t_server *s, char **arg);
char	*msz(t_server *s, char *arg);
char	*bct(t_server *s, char *arg);
char	*mct(t_server *s, char *arg);
char	*tna(t_server *s, char *arg);
char	*ppo(t_server *s, char *arg);
char	*plv(t_server *s, char *arg);
char	*pin(t_server *s, char *arg);
char	*sgt(t_server *s, char *arg);
char	*sst(t_server *s, char *arg);
char	*suc(t_server *s, char *arg);
int	see(t_client *this, t_server *server, char *arg);
int	set(t_client *this, t_server *server, char *arg);
int	take(t_client *this, t_server *server, char *arg);
int	left(t_client *this, t_server *server, char *arg);
int	walk(t_client *this, t_server *server, char *arg);
int	right(t_client *this, t_server *server, char *arg);
int	evict(t_client *this, t_server *server, char *arg);
int	egg_fork(t_client *this, t_server *server, char *arg);
int	broadcast(t_client *this, t_server *server, char *arg);
int	inventory(t_client *this, t_server *server, char *arg);
int	player_afk(t_client *this, t_server *server, char *arg);
int	connect_nbr(t_client *this, t_server *server, char *arg);
int	incantation(t_client *this, t_server *server, char *arg);
int	incantation_check(t_client *, t_server *, char *);
int	commands_set_timer(t_client *this, t_server *server, int time);
void	move_player_to(t_server *, t_client *, int, int);
t_server	*t_server_new(t_server_init var);
int		launch_server(t_server *this);
int		server_loop(t_server *server);
void		ser_del(void *this);
void	move(t_client *c);
void	see_add_player(t_field *field, char *stones);
void	see_add_stones(t_field *field, char *stones);
int	check_team(t_client *, t_server *, char *);
int	my_strcasecmp(const void *a, const void *b);
void	ser_del(void *this);
int	check_cmd(t_server* server, t_client* client);
int	set_numteam(t_server *server, t_client *client, char *buff);
int	write_fd(int fd, char *str);
int	kill_player(t_client *this, t_server *server);
void	graphic_end(t_server *server, char *team);
void	fuel_player(t_server *this);
void	refuel_eat(t_server *this);
void	fuel_init(t_server *this);
int	check_fd_graphics(t_server *s, fd_set *writefds, fd_set *readfds);
int	check_cmd_loop_graphics(t_server *s);
int	check_cmd_graphics(t_server *s, t_client *this);
int	delete_client(t_server*, t_client*);
int	remove_client(t_server*, t_client*);
int	ghosting_client(t_server*, t_client*);
int	graphic_conn(t_server *server, t_client *this);

# include "client.h"

#endif /* !SERVER_H_ */
