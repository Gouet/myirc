/*
** erase_client.c for ERASE in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May 17 13:27:33 2016 Victor Gouet
** Last update Tue May 24 11:15:41 2016 Victor Gouet
*/

#include <stdlib.h>
#include "../inc/server.h"

void		set_max_fd_on_channel(t_channel *channel)
{
  t_elem	*elem;
  int		fd;

  elem = channel->begin;
  fd = -1;
  while (elem)
    {
      if (fd < elem->client->fd)
	fd = elem->client->fd;
      elem = elem->next;
    }
  if (fd != -1)
    channel->max_fd = fd;
  else
    channel->max_fd = channel->ref_fd;
}

void		set_max_fd_on_list_channel(t_list *list_channel)
{
  t_channel	*channel;
  t_elem	*elem;
  int		fd;

  fd = -1;
  channel = list_channel->begin;
  while (channel)
    {
      elem = channel->begin;
      while (elem)
	{
	  fd = fd < elem->client->fd ? elem->client->fd : fd;
	  elem = elem->next;
	}
      channel = channel->next;
    }
  list_channel->max_fd = fd != -1 ? fd : list_channel->ref_fd;
}

t_elem		*erase_client_to_channel(t_channel *channel,
					 t_elem *client, t_list *list)
{
  t_elem	*elem;

  elem = channel->begin;
  if (elem == client)
    elem = NULL;
  if (get_duplicated_client(list, client->client) == 1)
    delete_client(client->client);
  while (elem)
    {
      if (elem->next == client)
	break;
      elem = elem->next;
    }
  if (elem)
    elem->next = client->next;
  if (channel->begin == client)
    channel->begin = channel->begin->next;
  if (channel->end == client)
    channel->end = elem;
  free(client);
  set_max_fd_on_channel(channel);
  if (channel->begin == NULL && channel->end == NULL)
    delete_channel(list, channel);
  return (elem != NULL ? elem->next : NULL);
}

void		*erase_client_to_the_server(t_client *client, t_list *list)
{
  t_elem	*elem;
  t_channel	*channel;
  int		changeChannel;

  channel = list->begin;
  while (channel)
    {
      changeChannel = 0;
      elem = channel->begin;
      while (elem)
	{
	  if (elem->client == client)
	    {
	      elem = erase_client_to_channel(channel, elem, list);
	      set_max_fd_on_list_channel(list);
	      channel = list->begin;
	      changeChannel = 1;
	      break;
	    }
	  elem = elem->next;
	}
      if (changeChannel == 0)
	channel = channel->next;
    }
  return (NULL);
}

