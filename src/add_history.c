/*
** add_history.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Fri Jun  3 23:58:39 2016 Saursinet
** Last update Sat Jun  4 01:29:10 2016 Saursinet
*/

#include "prototypes.h"

int	add_to_list(char *answer, char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    {
      if (strcmp(answer, tab[i]) == 0)
	return (0);
      ++i;
    }
  if (i == 30)
    {
      i = 0;
      free(tab[0]);
      while (tab[++i])
	tab[i - 1] = tab[i];
      tab[i - 1] = strdup(answer);
      tab[i] = NULL;
    }
  else
    {
      tab[i] = strdup(answer);
      tab[i + 1] = NULL;
    }
  return (0);
}

int	channel_list(int fd, char *str, t_user *user)
{
  char	*tmp;
  char	*tmp2;

  tmp = strdup(str);
  strtok(tmp, ":");
  tmp2 = strtok(NULL, ":");
  if (tmp2)
    add_to_list(tmp2, user->channel_list);
  answer_serv(fd, str, user);
  return (0);
}

int	user_list(int fd, char *str, t_user *user)
{
  char	*tmp;
  char	*tmp2;

  tmp = strdup(str);
  strtok(tmp, " ");
  strtok(NULL, " ");
  tmp2 = strtok(NULL, " ");
  if (tmp2)
    add_to_list(tmp2, user->client_list);
  answer_serv(fd, str, user);
  return (0);
}
