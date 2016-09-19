/*
** channels_gestion.c for CHANNEL in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May 17 12:03:00 2016 Victor Gouet
** Last update Fri Jun  3 10:58:10 2016 Victor Gouet
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "../inc/server.h"

t_elem		*get_client_channel(char const *channel_name,
				    t_client const *client,
				    t_list const *list)
{
  t_elem	*elem;
  t_channel	*channel;

  channel = list->begin;
  while (channel)
    {
      elem = channel->begin;
      if (channel->name &&
	  strcmp(channel_name, channel->name) == 0)
	while (elem)
	  {
	    if (elem->client == client)
	      return (elem);
	    elem = elem->next;
	  }
      channel = channel->next;
    }
  return (NULL);
}

t_channel	*get_channel(char const *channel_name,
			     t_list const *list)
{
  t_channel	*channel;

  channel = list->begin;
  while (channel)
    {
      if (channel->name &&
	  strcmp(channel_name, channel->name) == 0)
	return (channel);
      channel = channel->next;
    }
  return (NULL);
}

void		display_list(t_list const *channel_list)
{
  t_channel	*channel;
  t_elem	*elem;
  int		i;

  channel = channel_list->begin;
  printf("display_list:\n");
  i = 1;
  while (channel)
    {
      printf("begin channel %d =>\n", i);
      elem = channel->begin;
      while (elem)
	{
	  printf("elem => %p | fd => %d | named => %s\n", elem,
		 elem->client->fd, elem->client->nick ?
		 elem->client->nick : "unknown");
	  elem = elem->next;
	}
      printf("end channel %d\n", i);
      ++i;
      channel = channel->next;
    }
  printf("--end--\n\n");
}

int		send_ring_buffer_to_client(t_list *list)
{
  t_elem	*elem;

  if (list->begin)
    {
      elem = list->begin->begin;
      while (elem)
	{
	  flush(elem->client);
	  elem = elem->next;
	}
    }
  return (0);
}

int		channels_gestion(t_list *channel_list, fd_set *fds)
{
  if (channel_list->begin)
    {
      clients_gestion(channel_list->begin, fds, channel_list);
      send_ring_buffer_to_client(channel_list);
    }
  return (0);
}
