/*
** dico.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 23 14:44:48 2016 Saursinet
** Last update Sat Jun  4 00:45:18 2016 Saursinet
*/

#include <string.h>
#include <stdlib.h>
#include "prototypes.h"

int		init_fptr(t_dico *dico)
{
  dico->ptr[0] = &connect_to_serv;
  dico->ptr[1] = &basic_answer;
  dico->ptr[2] = &basic_answer;
  dico->ptr[3] = &basic_answer;
  dico->ptr[4] = &basic_answer;
  dico->ptr[5] = &basic_answer;
  dico->ptr[6] = &basic_answer;
  dico->ptr[7] = &basic_answer;
  dico->ptr[8] = &send_file;
  dico->ptr[9] = &recv_file;
  dico->ptr[10] = &basic_answer;
  dico->ptr[11] = &answer_serv;
  dico->ptr[12] = &answer_serv;
  dico->ptr[13] = &answer_serv;
  dico->ptr[14] = &channel_list;
  dico->ptr[15] = &user_list;
  dico->ptr[16] = &answer_serv;
  dico->ptr[17] = &answer_serv;
  dico->ptr[18] = &answer_serv;
  dico->ptr[19] = &get_ip_and_port;
  dico->ptr[20] = &get_ip_and_port;
  dico->ptr[21] = &basic_answer;
  return (0);
}

int		init_serv(t_dico *dico)
{
  dico->serv[0] = strdup("SERVER ");
  dico->serv[1] = strdup("NICK ");
  dico->serv[2] = strdup("LIST ");
  dico->serv[3] = strdup("JOIN ");
  dico->serv[4] = strdup("PART ");
  dico->serv[5] = strdup("USERS ");
  dico->serv[6] = strdup("NAMES ");
  dico->serv[7] = strdup("PRIVMSG ");
  dico->serv[8] = strdup("SEND ");
  dico->serv[9] = strdup("ACCEPT ");
  dico->serv[10] = strdup("QUIT ");
  dico->serv[19] = strdup("PRIVMSG ");
  dico->serv[21] = strdup("PRIVMSG ");
  return (init_fptr(dico));
}

int		init_dico(t_dico *dico)
{
  dico->cmd[0] = strdup("/server");
  dico->cmd[1] = strdup("/nick");
  dico->cmd[2] = strdup("/list");
  dico->cmd[3] = strdup("/join");
  dico->cmd[4] = strdup("/part");
  dico->cmd[5] = strdup("/users");
  dico->cmd[6] = strdup("/names");
  dico->cmd[7] = strdup("/msg");
  dico->cmd[8] = strdup("/send_file");
  dico->cmd[9] = strdup("/accept_file");
  dico->cmd[10] = strdup("/quit");
  dico->cmd[11] = strdup(":VictorServer 001");
  dico->cmd[12] = strdup(":VictorServer 331");
  dico->cmd[13] = strdup(":VictorServer 366");
  dico->cmd[14] = strdup("!~VictorServer JOIN");
  dico->cmd[15] = strdup(":VictorServer 393");
  dico->cmd[16] = strdup(":VictorServer 353");
  dico->cmd[17] = strdup(":VictorServer 321");
  dico->cmd[18] = strdup(":VictorServer 323");
  dico->cmd[19] = strdup(":VictorServer 102");
  dico->cmd[20] = strdup(":VictorServer 103");
  dico->cmd[21] = NULL;
  return (init_serv(dico));
}

void		clear_dico(t_dico *dico)
{
  int		i;

  i = 0;
  while (i < 19)
    free(dico->cmd[i++]);
  i = 0;
  while (i < 11)
    free(dico->serv[i++]);
  free(dico->serv[19]);
}
