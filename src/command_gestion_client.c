/*
** command_gestion_client.c for COMMAND CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May 17 16:02:50 2016 Victor Gouet
** Last update Mon May 30 11:40:35 2016 Victor Gouet
*/

#include <string.h>
#include <stdlib.h>
#include "../inc/server.h"

int	        on_list(t_list *list, t_elem *elem, char **tab)
{
  t_channel	*channel;

  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  msg_to_client(elem->client, ":%s 321 %s Channel :Users Name\r\n",
		SERVERNAME, elem->client->nick);
  channel = NULL;
  if (list->begin)
    channel = list->begin->next;
  while (channel)
    {
      if ((tab[1] && contain_string(channel->name, tab[1]) == 0)
	  || tab[1] == NULL)
	msg_to_client(elem->client, ":%s 322 %s %s :\r\n",
		      SERVERNAME, elem->client->nick, channel->name);
      channel = channel->next;
    }
  msg_to_client(elem->client, ":%s 323 %s :End of /LIST\r\n",
		SERVERNAME, elem->client->nick);
  return (0);
}

int		on_names(t_list *list, t_elem *elem, char **tab)
{
  char		name[4096];

  bzero(name, sizeof(name));
  strcpy(name, "*\0");
  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  if (tab[1])
    {
      send_names_command(name, tab, elem, list);
    }
  return (msg_to_client(elem->client,
			":%s 366 %s %s :End of /NAMES list.%s",
			SERVERNAME, elem->client->nick, name, CRLF), 0);
}

int		on_users(t_list *list, t_elem *elem, char **tab)
{
  t_elem	*tmp;
  int		users_nbrs;

  (void)tab;
  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  tmp = NULL;
  users_nbrs = 0;
  if (list->begin)
    tmp = list->begin->begin;
  msg_to_client(elem->client, ":%s 392 %s\r\n",
		SERVERNAME, ":UserID Terminal Hôte");
  while (tmp)
    {
      msg_to_client(elem->client, ":%s 393 %s\r\n", SERVERNAME, tmp->client->nick);
      ++users_nbrs;
      tmp = tmp->next;
    }
  if (users_nbrs == 0)
    msg_to_client(elem->client, ":%s 395 %s\r\n", SERVERNAME, ":Nobody logged in");
  msg_to_client(elem->client, ":%s 394 %s\r\n",
		SERVERNAME, ":Nobody logged in");
  return (0);
}

static int	name_collision(t_elem *ref, char *nick,
			       t_list *list, int flags)
{
  t_channel	*channel;
  t_elem	*elem;

  channel = list->begin;
  while (channel)
    {
      elem = channel->begin;
      while (elem)
	{
	  if (ref != elem && elem->client->nick
	      && strcmp(nick, elem->client->nick) == 0)
	    {
	      if (flags == DELETE)
		{
		  free(elem->client->nick);
		  elem->client->nick = NULL;
		}
	      else
		return (-1);
	    }
	  elem = elem->next;
	}
      channel = channel->next;
    }
  return (0);
}

int		on_nick(t_list *list, t_elem *elem, char **tab)
{
  char		prev_nick[4096];

  if (tab[1] == NULL)
    return (msg_to_client(elem->client, ":%s %s", SERVERNAME,
			  ERR_NONICKNAMEGIVEN), 0);
  if (strlen(tab[1]) > 9)
    return (msg_to_client(elem->client, ":%s %s", SERVERNAME,
			  ERR_ERRONEUSNICKNAME), 0);
  bzero(prev_nick, sizeof(prev_nick));
  if (name_collision(elem, tab[1], list, NOTHING) == -1)
    return (msg_to_client(elem->client, ":%s %s", SERVERNAME,
			  ERR_NICKNAMEINUSE), 0);
  if (elem->client->nick)
    {
      strcpy(prev_nick, elem->client->nick);
      free(elem->client->nick);
    }
  if ((elem->client->nick = strdup(tab[1])) == NULL)
    return (-1);
  msg_to_client(elem->client, ":%s!~%s NICK :%s\r\n", prev_nick, SERVERNAME,
		elem->client->nick);
  return (0);
}
