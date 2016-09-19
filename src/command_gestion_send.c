/*
** command_gestion_send.c for COMMAND CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Tue May 17 16:04:06 2016 Victor Gouet
** Last update Fri Jun  3 11:04:22 2016 Victor Gouet
*/

#include <string.h>
#include "../inc/server.h"
#include "../lib/storage.h"

char	*get_message(char *tab, char *buffer)
{
  int		i;
  int		space;
  char		isSpace;

  i = 0;
  space = 0;
  while (buffer[i] != '\r' && buffer[i] != '\0')
    {
      isSpace = 0;
      while (buffer[i] == ' ' && buffer[i] != '\r' && buffer[i] != '\0')
	{
	  isSpace = 1;
	  ++i;
	}
      if (isSpace)
	space += 1;
      if (space >= 2 && strcmp(&buffer[i], tab) > 0)
	break;
      if (buffer[i] != '\r' && buffer[i] != '\0')
	++i;
    }
  if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\r')
    buffer[strlen(buffer) - 1] = '\0';
  return (&buffer[i]);
}

int	        on_send_priv(t_list *list, t_elem *elem,
			     char **tab, char *buffer)
{
  t_channel	*channel;
  t_elem	*user;
  char		*msg;

  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  if (!tab[1])
    return (msg_to_client(elem->client, ":%s 411 %s :No recipient given\r\n",
			  SERVERNAME, elem->client->nick));
  if (!tab[2])
    return (msg_to_client(elem->client, ":%s 412 %s :No text to send\r\n",
			  SERVERNAME, elem->client->nick));
  msg = STRING(":%s!~%s PRIVMSG %s :%s\r\n", elem->client->nick, SERVERNAME,
	       tab[1], get_message(tab[2], buffer));
  if ((channel = get_channel(tab[1], list)) != NULL && msg)
    send_msg_to_channel(channel, elem->client, msg);
  else if ((user = get_client_from_name(list, tab[1])) != NULL && msg)
    bufferise(user->client, msg);
  else
    msg_to_client(elem->client, ":%s 401 %s %s %s", SERVERNAME,
		  elem->client->nick, tab[1], ":No such nick/channel\r\n");
  if (msg)
    free(msg);
  return (0);
}

int		on_send_file(t_list *list, t_elem *elem, char **tab)
{
  t_elem	*client;

  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  if (!tab[1] || !tab[2])
    return (msg_not_enough_param(elem->client, tab[0]));
  if ((client = get_client_from_name(list, tab[1])) == NULL)
    return (msg_to_client(elem->client, ":%s %s", SERVERNAME,
			  ERR_UNKNOWNCLIENT), 0);
  msg_to_client(client->client,
		":%s 102 {nick=%s, file=%s, ip=%s, port=%s}\r\n",
		SERVERNAME, elem->client->nick, tab[2],
		elem->client->ip, DEFAUTLUSERPORT);
  msg_to_client(elem->client, ":%s 108 SEND ok.\r\n", SERVERNAME);
  client->client->actual_file = strdup(tab[2]);
  client->client->actual_user = strdup(elem->client->nick);
  return (0);
}

int		on_accept_file(t_list *list, t_elem *elem, char **tab)
{
  t_elem	*client;

  if (is_authentificated(elem->client))
    return (msg_not_register(elem->client, tab[0]));
  if (!tab[1])
    return (msg_not_enough_param(elem->client, tab[0]));
  if (!elem->client->actual_user || !elem->client->actual_file
      || strcmp(tab[1], elem->client->actual_user) != 0)
    return (msg_to_client(elem->client, ":%s 105 %s\r\n", SERVERNAME,
			  "can t accept"));
  if ((client = get_client_from_name(list, elem->client->actual_user)) == NULL)
    return (msg_to_client(elem->client, ":%s %s", SERVERNAME,
			  ERR_UNKNOWNCLIENT), 0);
  msg_to_client(client->client,
		":%s 103 {nick=%s, file=%s, ip=%s, port=%s}\r\n",
		SERVERNAME, elem->client->nick, elem->client->actual_file,
		elem->client->ip, DEFAUTLUSERPORT);
  msg_to_client(elem->client, ":%s 108 ACCEPT ok.\r\n", SERVERNAME);
  free(elem->client->actual_file);
  free(elem->client->actual_user);
  elem->client->actual_file = NULL;
  elem->client->actual_user = NULL;
  return (0);
}
