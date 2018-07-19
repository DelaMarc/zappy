/*
** stones.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy/include
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jun 10 23:35:30 2016 Loïc GIGOMAS
** Last update Fri Jun 24 02:41:19 2016 Loïc GIGOMAS
*/

#ifndef STONE_H_
# define STONE_H_

typedef enum	e_stoneType
  {
    nourriture,
    linemate,
    deraumere,
    sibur,
    mendiane,
    phiras,
    thystame
  }		t_stoneType;

extern const char * const stoneName[];

# define STONE_NBR	7

#endif /* !STONE_H_ */
