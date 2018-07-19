/*
** lambdas.h for Zappy in /home/gigoma_l/rendu/PSU_2015_zappy
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jun 11 19:33:27 2016 Loïc GIGOMAS
** Last update Wed Jun 22 15:54:26 2016 Loïc GIGOMAS
*/

#ifndef LAMBDA_H_
# define LAMBDA_H_

/*
** La lambda (ne pas confondre avec "lambada") permet de créer des
** fonctions anonymes, qui ont accès aux variables de la fonction parent.
** r = Return (like "double" or "void *")
** p = params (like "(int var_a, char var_b)" => dont forget '(' and ')'
** b = Block (the function itself, you don't have to declare it, just {...})
*/
# define FUNCTION(ret, params, block) ({ret _lamb params block &_lamb;})

#endif /* !LAMBDA_H_ */
