##
## Makefile for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
##
## Made by Loïc GIGOMAS
## Login   <gigoma_l@epitech.net>
##
## Started on  Fri Jun 10 21:11:02 2016 Loïc GIGOMAS
## Last update Sun Jun 26 15:25:50 2016 Maxime Cohen
##

BIN_SERVER	= zappy_server

BIN_CLIENT	= zappy_ai

SRC_SERVER	= main.c \
		  ../stones.c \
		  refuel.c \
		  server.c \
		  server2.c \
		  bind.c \
		  select.c \
		  check_cmd.c \
		  check_team.c \
		  kill_player.c \
		  create_client.c \
		  serv_getvals.c \
		  serv_getvals2.c \
		  write_graphic.c \
		  get_next_line.c \
		  see.c \
		  set.c \
		  take.c \
		  left.c \
		  walk.c \
		  right.c \
		  evict.c \
		  egg_fork.c \
		  broadcast.c \
		  inventory.c \
		  player_afk.c \
		  connect_nbr.c \
		  incantation.c \
		  commands_func.c \
		  eggs.c \
		  ghosting.c \
		  graphic_cmd.c \
		  graphic_cmd2.c \
		  graphic_cmd3.c \
		  ../iov.c \
		  ../new.c \
		  ../circularBuff.c \
		  ../list_accessors.c\
		  ../list_modifiers.c\
		  ../vector_modifiers.c \
		  ../vector_accessors.c \
		  ../vector2d_modifiers.c \
		  ../vector2d_accessors.c \
		  ../team_accessors.c \
		  ../team_modifiers.c \
		  ../field_accessors.c \
		  ../field_modifiers.c \
		  ../client_accessors.c \
		  ../map_accessors.c \
		  ../map_modifiers.c \
		  ../pair.c \
		  ../timer.c

SRC_CLIENT	= main.c \
		  select.c \
		  client.c \
		  client_read.c \
		  ai.c \
		  ai_links.c \
		  markov_modifiers.c \
		  markov_accessors.c \
		  states_1.c \
		  iov.c \
		  command_move.c \
		  command_objet.c \
		  command_other.c \
		  parse_reply.c \
		  parse_voir.c \
		  mandat.c \
		  ../new.c \
		  ../stones.c \
		  ../vector_modifiers.c \
		  ../vector_accessors.c \
		  ../circularBuff.c


CC		= gcc

CFLAGS		+= -W -Wall -Wextra -std=gnu99
CFLAGS		+= -I include/

LDFLAGS		= -lm

RM		= rm -f

SRCDSTCOM	= src

SRCDST1		= $(SRCDSTCOM)/server

SRCDST2		= $(SRCDSTCOM)/client

OBJDSTCOM	= obj

OBJDST1		= $(OBJDSTCOM)/server

OBJDST2		= $(OBJDSTCOM)/client

SRC1		= $(addprefix $(SRCDST1)/, $(SRC_SERVER))

SRC2		= $(addprefix $(SRCDST2)/, $(SRC_CLIENT))

OBJ_SERVER	= $(addsuffix .o, $(basename $(subst $(SRCDST1), $(OBJDST1), $(SRC1))))

OBJ_CLIENT	= $(addsuffix .o, $(basename $(subst $(SRCDST2), $(OBJDST2), $(SRC2))))

all		: $(BIN_SERVER) $(BIN_CLIENT)
		  @echo -e "\033[32mPlease do '\033[1msource autocompletion\033[0;32m' in your shell.\033[0m"

$(OBJDST1)/%.o	: $(SRCDST1)/%.c
		  @mkdir -p $(OBJDST1)
		  $(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJDST2)/%.o	: $(SRCDST2)/%.c
		  @mkdir -p $(OBJDST2)
		  $(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BIN_SERVER)	: $(OBJ_SERVER)
		  $(CC) $(CFLAGS) $(OBJ_SERVER) -o $(BIN_SERVER) $(LDFLAGS)

$(BIN_CLIENT)	: $(OBJ_CLIENT)
		  $(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(BIN_CLIENT) $(LDFLAGS)

clean		:
		  $(RM) $(OBJ_SERVER)
		  $(RM) $(OBJ_CLIENT)

fclean		: clean
		  $(RM) $(BIN_SERVER)
		  $(RM) $(BIN_CLIENT)

re		: fclean all

.PHONY		: all clean flcean re
