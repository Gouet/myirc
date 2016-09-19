/*
** clients_gestion.c for CLIENTS in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May 16 20:24:28 2016 Victor Gouet
** Last update Fri Jun  3 11:03:59 2016 Victor Gouet
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/server.h"

static t_command	command[COMMAND_SIZE] = {
  {"/nick", "NICK", on_nick},
  {"/list", "LIST", on_list},
  {"/join", "JOIN", on_join},
  {"/part", "PART", on_part},
  {"/users", "USERS", on_users},
  {"/msg", "PRIVMSG", on_send_priv},
  {"/send_file", "SEND", on_send_file},
  {"/accept_file", "ACCEPT", on_accept_file},
  {"/names", "NAMES", on_names},
  {"/user", "USER", on_user},
  {"/quit", "QUIT", on_quit}
};

int		send_msg_to_channel(t_channel *channel,
				    t_client const *ref,
				    char *msg)
{
  t_elem	*elem;

  elem = channel->begin;
  while (elem)
    {
      if (ref != elem->client)
	{
	  bufferise(elem->client, msg);
	}
      elem = elem->next;
    }
  return (0);
}

int		client_input(t_channel *channel,
			     t_list *list,
			     t_elem *elem,
			     char *buffer)
{
  char		**tab;
  int		i;
  int		size;

  (void)channel;
  i = 0;
  if ((tab = str_to_word_tab(buffer)) == NULL)
    return (-1);
  if (tab[0] != NULL)
    while (i < COMMAND_SIZE)
      {
	if (strcmp(command[i].command, tab[0]) == 0
	    || strcasecmp(command[i].case_command, tab[0]) == 0)
	  {
	    size = command[i].fptr(list, elem, tab, buffer);
	    delete_command(tab, buffer);
	    return (size);
	  }
	++i;
      }
  msg_to_client(elem->client, ":%s 421 %s %s %s", SERVERNAME,
		elem->client->nick, tab[0], ":Unknown command\r\n");
  delete_command(tab, buffer);
  return (0);
}

int		clients_gestion(t_channel *channel, fd_set *fds,
				t_list *list)
{
  t_elem	*elem;
  char		*buffer;

  elem = channel->begin;
  while (elem)
    {
      if (is_client_already_managed(list, elem) == 1
	  && FD_ISSET(elem->client->fd, fds))
	{
	  if (!(buffer = recv_msg_from_client(elem->client)))
	    {
	      elem = erase_client_to_the_server(elem->client, list);
	      continue;
	    }
	  if (client_input(channel, list, elem, buffer) == -1)
	    {
	      elem = erase_client_to_the_server(elem->client, list);
	      continue;
	    }
	}
      elem = elem->next;
    }
  return (0);
}
