/*
** command_gestion_channel.c for COMMAND CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May 17 16:03:30 2016 Victor Gouet
** Last update Fri Jun  3 11:02:36 2016 Victor Gouet
*/

#include <string.h>
#include "../lib/storage.h"
#include "../inc/server.h"

static int	channel_is_valid(char *channel)
{
  int		i;

  i = 0;
  while (channel[i])
    {
      if (channel[i] == ' ' || channel[i] == 7)
	return (-1);
      ++i;
    }
  if (channel[0] == '#' || channel[0] == '&' ||
      channel[0] == '+' || channel[0] == '!')
    return (0);
  return (-1);
}

static t_channel	*on_channel(t_list *list,
				    t_elem *elem, char *name)
{
  t_channel	*newchannel;

  newchannel = list->begin;
  while (newchannel)
    {
      if (newchannel->name && strcmp(name, newchannel->name) == 0)
	{
	  return (newchannel);
	}
      newchannel = newchannel->next;
    }
  if ((newchannel = new_channel(list)) == NULL)
    {
      msg_to_client(elem->client, ":%s 461 :Not enough parameters\r\n",
		    SERVERNAME);
      return (NULL);
    }
  newchannel->name = name;
  return (newchannel);
}

static void	connect_channel(t_channel *newchannel, t_elem *elem,
				t_list *list)
{
  t_elem	*tmp;
  t_elem	*newelem;
  char		*msg;

  if (newchannel == NULL || elem == NULL || elem->client == NULL
      || is_client_already_on_channel(newchannel, elem->client) == -1 ||
      (newelem = new_clients(list, elem->client, NONE)) == NULL)
    return ;
  if (newchannel->begin == NULL && newchannel->end == NULL)
    newchannel->begin = newelem;
  else
    newchannel->end->next = newelem;
  newchannel->end = newelem;
  msg = STRING(":%s!~%s JOIN :%s\r\n", elem->client->nick,
	       SERVERNAME, newchannel->name);
  bufferise(elem->client, msg);
  send_msg_to_channel(newchannel, elem->client, msg);
  tmp = newchannel->begin;
  msg_to_client(elem->client, ":%s 353 %s = %s :", SERVERNAME,
		elem->client->nick, newchannel->name);
  on_join_gestion(elem->client, tmp);
  msg_to_client(elem->client, ":%s 366 %s %s :End of /NAMES list.\r\n",
		SERVERNAME, elem->client->nick, newchannel->name);
}

int	        on_join(t_list *list, t_elem *elem, char **tab)
{
  char		**cannaux;
  int		i;
  int		a;

  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  if (i = 0, tab[1] == NULL)
    return (msg_not_enough_param(elem->client, tab[0]));
  while (tab[++i] != NULL)
    {
      if ((cannaux = split(tab[i], ',')) == NULL)
	return (msg_not_enough_param(elem->client, tab[0]));
      a = -1;
      while (cannaux[++a])
	{
	  if (channel_is_valid(cannaux[a]) == -1)
	    msg_to_client(elem->client, ":%s 403 %s %s :No such channel\r\n",
			  SERVERNAME, elem->client->nick, cannaux[a]);
	  else
	    connect_channel(on_channel(list, elem, cannaux[a]),
	  		    elem, list);
	}
    }
  return (0);
}

int		on_part(t_list *list, t_elem *elem, char **tab)
{
  char		**cannaux;
  int		i;
  int		a;

  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  if (i = 0, tab[1] == NULL)
    {
      msg_not_enough_param(elem->client, tab[0]);
      return (0);
    }
  while (tab[++i] != NULL)
    {
      if ((cannaux = split(tab[i], ',')) == NULL)
	{
	  msg_not_enough_param(elem->client, tab[0]);
	  return (0);
	}
      a = -1;
      while (cannaux[++a])
	{
	  leave_channel(list, cannaux[a], elem->client);
	}
    }
  return (0);
}
