/*
** client_info.c for INFO in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed May 18 21:18:57 2016 Victor Gouet
** Last update Tue May 24 12:12:53 2016 Victor Gouet
*/

#include <string.h>
#include "../inc/server.h"

int		get_duplicated_client(t_list const *list,
				      t_client const *client)
{
  int		i;
  t_channel	*channel;
  t_elem	*elem;

  i = 0;
  channel = list->begin;
  while (channel)
    {
      elem = channel->begin;
      while (elem)
	{
	  if (client == elem->client)
	    ++i;
	  elem = elem->next;
	}
      channel = channel->next;
    }
  return (i);
}

int		is_client_already_managed(t_list const *list,
					  t_elem const *elem_client)
{
  t_channel	*channel;
  t_elem	*elem;

  channel = list->begin;
  while (channel)
    {
      elem = channel->begin;
      while (elem)
	{
	  if (elem_client == elem)
	    return (1);
	  if (elem_client->client->fd == elem->client->fd)
	    return (-1);
	  elem = elem->next;
	}
      channel = channel->next;
    }
  return (1);
}

int		is_client_already_on_channel(t_channel const *channel,
					     t_client const *client)
{
  t_elem	*elem;

  elem = channel->begin;
  while (elem)
    {
      if (elem->client == client)
	return (-1);
      elem = elem->next;
    }
  return (0);
}

t_elem		*get_client_from_name(t_list const *list,
				      char const *name)
{
  t_elem	*elem;

  elem = NULL;
  if (list->begin)
    elem = list->begin->begin;
  while (elem)
    {
      if (elem->client->nick && strcmp(name,
				       elem->client->nick) == 0)
	return (elem);
      elem = elem->next;
    }
  return (NULL);
}

int		is_authentificated(t_client *client)
{
  if (client->hostname
      && client->nick
      && client->realname
      && client->servername
      && client->username)
    return (0);
  return (-1);
}
