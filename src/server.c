/*
** server.c for SAURSINET in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May 16 18:47:41 2016 Victor Gouet
** Last update Wed May 25 21:57:43 2016 Victor Gouet
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../inc/server.h"

int		create_server(int const port)
{
  int		server_fd;

  if ((server_fd = get_fd_with_protocol_name("TCP")) == -1)
    {
      write(2, "get_fd_with_protocol_name failed\n", 33);
      return (-1);
    }
  if (bind_socketaddr(server_fd, port) == -1)
    {
      write(2, "bind_socketaddr failed\n", 23);
      return (close_socket_fd(server_fd), -1);
    }
  if (create_queue(server_fd, 118) == -1)
    {
      write(2, "create_queue failed\n", 20);
      return (close_socket_fd(server_fd), -1);
    }
  return (server_fd);
}

static int	init_select(fd_set *fds, int const server,
			    t_list *channel_list)
{
  t_channel	*channel;
  t_elem	*elem;

  FD_ZERO(fds);
  FD_SET(server, fds);
  channel = channel_list->begin;
  elem = NULL;
  if (channel)
    elem = channel->begin;
  while (elem)
    {
      FD_SET(elem->client->fd, fds);
      elem = elem->next;
    }
  if (select(channel_list->max_fd + 1, fds, NULL, NULL, NULL) == -1)
    {
      fprintf(stderr, "select failed\n");
      return (-1);
    }
  return (0);
}

int		run_server(int const server)
{
  t_client	*client;
  t_list	channel_list;
  fd_set	fds;

  new_lists(&channel_list, server);
  while (42)
    {
      if (init_select(&fds, server, &channel_list) == -1)
	return (-1);
      if (FD_ISSET(server, &fds))
	{
	  if ((client = get_client_from_server(server)) == NULL)
	    return (close_socket_fd(server), -1);
	  new_clients(&channel_list, client, DEFAULT);
	}
      else
	{
	  channels_gestion(&channel_list, &fds);
	}
    }
  return (close_socket_fd(server), 0);
}
