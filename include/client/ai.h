#ifndef AI_H_
# define AI_H_

# include "client/client.h"

typedef int	(*t_state_f)(t_client *);

typedef enum	e_aiNodes
  {
    INITIAL,
    COM_FORWARD,
    COM_RIGHT,
    COM_LEFT,
    COM_SEE,
    COM_INV,
    TAKEFOOD,
    COM_EXPUL,
    COM_BROADCST,
    COM_TAKE,
    COM_PUT,
    COM_INCANT,
    COM_FORK,
    COM_SLOT
  }		t_aiNodes;

int	set_ai(t_client *c);
int	add_node(t_client *c, void *data);
int	add_link(t_markov_node *n, size_t min, size_t max, size_t i);

int	ai_links_1(t_client *c);

int	state_initial(t_client *c);
int	state_wait(t_client *c);
void	init_take_food(void *c);
int	state_take_food(t_client *c);

int	mandat(t_client *c);

#endif /* !AI_H_ */
