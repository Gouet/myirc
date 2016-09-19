/*
** command_gestion_user.c for USER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May 23 10:16:51 2016 Victor Gouet
** Last update Mon May 30 11:59:27 2016 Victor Gouet
*/

#include <string.h>
#include "../lib/storage.h"
#include "../inc/server.h"

static int      is_valid_user_args(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    {
      ++i;
    }
  if (i < 5)
    {
      return (-1);
    }
  return (0);
}

void	send_msg_to_all_before_quit(t_list const *list,
				    t_elem const *ref,
				    char *msg1)
{
  t_elem	*elem;
  t_channel	*channel;
  char		*msg;

  channel = NULL;
  if (list->begin)
    channel = list->begin->next;
  msg = STRING(":%s!~%s QUIT: %s\r\n", ref->client->nick, SERVERNAME, msg1);
  while (channel)
    {
      elem = channel->begin;
      while (elem)
	{
	  if (ref->client == elem->client && msg)
	    {
	      send_msg_to_channel(channel, ref->client, msg);
	    }
	  elem = elem->next;
	}
      channel = channel->next;
    }
}

int	on_quit(t_list *list, t_elem *elem,
		char **tab, char *buffer)
{
  if (tab[1])
    {
      send_msg_to_all_before_quit(list, elem, get_message(tab[1], buffer));
      msg_to_client(elem->client, "ERROR :Closing Link: %s[%s] (Quit: %s)\r\n",
		    elem->client->nick, SERVERNAME,
		    get_message(tab[1], buffer));
    }
  else
    {
      send_msg_to_all_before_quit(list, elem, elem->client->nick);
      msg_to_client(elem->client, "ERROR :Closing Link: %s[%s] (Quit: %s)\r\n",
		    elem->client->nick, SERVERNAME, elem->client->nick);
    }
  return (-1);
}

int	on_user(t_list *list, t_elem *elem,
		char **tab, char *buffer)
{
  char	*str;

  (void)list;
  if (is_valid_user_args(tab) == -1)
    return (msg_not_enough_param(elem->client, tab[0]));
  if ((elem->client->username = strdup(tab[1])) == NULL)
    return (-1);
  if ((elem->client->hostname = strdup(tab[2])) == NULL)
    return (-1);
  if ((elem->client->servername = strdup(tab[3])) == NULL)
    return (-1);
  str = rindex(buffer, ':');
  if (str)
    {
      if ((elem->client->realname = strdup(str)) == NULL)
	return (-1);
      elem->client->realname[strlen(elem->client->realname) - 1] = '\0';
    }
  else
    if ((elem->client->realname = strdup(tab[4])) == NULL)
      return (-1);
  msg_to_client(elem->client, ":%s 001 %s: Welcome !\r\n", SERVERNAME,
		elem->client->nick);
  return (0);
}
