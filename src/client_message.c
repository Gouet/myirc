/*
** client_message.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Tue May 31 15:22:38 2016 Saursinet
** Last update Fri Jun  3 00:00:40 2016 Saursinet
*/

#include "prototypes.h"

int	answer_serv(int fd, char *str, t_user *user)
{
  (void)fd;
  (void)user;
  printf("Serv answer :[%s]\n", str);
  return (0);
}

int	add_to_history(t_user *user, char *answer)
{
  int	i;

  i = 0;
  while (user->history[i])
    ++i;
  if (i == 39)
    {
      i = 0;
      free(user->history[0]);
      while (user->history[++i])
	user->history[i - 1] = user->history[i];
      user->history[i - 1] = strdup(answer);
      user->history[i] = NULL;
    }
  else
    {
      user->history[i] = strdup(answer);
      user->history[i + 1] = NULL;
    }
  return (0);
}

void	fill_final(char *final, char *cmd, char *str, int i)
{
  strcat(final, cmd);
  if (i == 7)
    strcat(final, strtok(NULL, "\0"));
  else
    strcat(final, str);
}

int	basic_answer(int fd, char *str, t_user *user)
{
  char	*tmp;
  char	final[4096];
  int	i;

  if (fd == -1)
    return (1);
  tmp = strdup(str);
  strtok(tmp, " ");
  bzero(final, 4096);
  i = 0;
  while (user->dico.cmd[i] && strstr(str, user->dico.cmd[i]) == NULL)
    ++i;
  if (user->dico.cmd[i] && i != 7)
    {
      strcat(final, user->dico.serv[i]);
      strcat(final, (tmp = strtok(NULL, "")) == NULL ? "" : tmp);
    }
  else
    fill_final(final, user->dico.serv[i], str, i);
  add_to_history(user, final);
  strcat(final, "\r\n");
  printf("[%s]\n", final);
  send_msg_to_server(user, final, 0);
  return (0);
}

int	check_answer(char *answer, t_user *user, int opt)
{
  int	i;

  if (answer)
    {
      if (i = 0, user->graphic_mode == 1 && opt == 1)
	add_to_history(user, answer);
      if (answer[0] == '4')
	printf("Err :%s\n", answer);
      else if (strstr(answer, ":{file="))
	get_ip_and_port(answer, user);
      else if (strstr(answer, "ready to connect"))
	send_complete(user);
      else
	{
	  while (user->dico.cmd[i] && strstr(answer, user->dico.cmd[i]) == NULL)
	    ++i;
	  if (user->dico.cmd[i])
	    user->dico.ptr[i](user->sock.fd, answer, user);
	  else if (opt == 1)
	    printf("Serv answer :[%s]\n", answer);
	  else
	    user->dico.ptr[i](user->sock.fd, answer, user);
	}
    }
  return (answer ? free(answer) : 0, 0);
}
