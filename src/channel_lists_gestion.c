/*
** channel_lists_gestion.c for CHANNEL LIST in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May 17 11:04:40 2016 Victor Gouet
** Last update Wed May 18 23:38:51 2016 Victor Gouet
*/

#include <stdlib.h>
#include "../inc/server.h"

void		new_lists(t_list *list, int const server)
{
  list->begin = NULL;
  list->end = NULL;
  list->max_fd = server;
  list->ref_fd = server;
}

t_elem		*new_clients(t_list *list,
			     t_client *client,
			     CHANNEL type)
{
  t_elem	*elem;

  if ((elem = malloc(sizeof(t_elem))) == NULL)
    return (NULL);
  elem->next = NULL;
  elem->client = client;
  list->max_fd = client->fd > list->max_fd ? client->fd : list->max_fd;
  if (type == NONE)
    return (elem);
  if (!list->begin)
    if ((list->begin = new_channel(list)) == NULL)
      return (NULL);
  if (list->begin->begin == NULL && list->begin->end == NULL)
    {
      list->begin->begin = elem;
    }
  else
    {
      list->begin->end->next = elem;
    }
  list->begin->end = elem;
  return (elem);
}

t_channel	*new_channel(t_list *list)
{
  t_channel	*channel;

  if ((channel = malloc(sizeof(t_channel))) == NULL)
    return (NULL);
  channel->begin = NULL;
  channel->end = NULL;
  channel->max_fd = list->max_fd;
  channel->ref_fd = list->max_fd;
  channel->next = NULL;
  channel->name = NULL;
  channel->topic = NULL;
  if (list->begin == NULL && list->end == NULL)
    {
      list->begin = channel;
    }
  else
    {
      list->end->next = channel;
    }
  list->end = channel;
  return (channel);
}

void		delete_all_clients(t_channel *channel, t_list *list)
{
  t_elem	*elem;
  t_elem	*tmp;

  tmp = NULL;
  elem = channel->begin;
  while (elem)
    {
      if (tmp)
	{
	  if (get_duplicated_client(list, tmp->client) == 1)
	    delete_client(tmp->client);
	  free(tmp);
	}
      tmp = elem;
      elem = elem->next;
    }
  if (tmp)
    {
      if (get_duplicated_client(list, tmp->client) == 1)
      	delete_client(tmp->client);
      free(tmp);
    }
  free(channel);
}

t_channel	*delete_channel(t_list *list,
				t_channel *channel)
{
  t_channel	*elem;

  elem = list->begin;
  if (elem == channel)
    elem = NULL;
  while (elem)
    {
      if (elem->next == channel)
	break;
      elem = elem->next;
    }
  if (elem)
    elem->next = channel->next;
  if (list->begin == channel)
    list->begin = list->begin->next;
  if (list->end == channel)
    list->end = elem;
  delete_all_clients(channel, list);
  return (elem != NULL ? elem->next : NULL);
}
