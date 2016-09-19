/*
** leave_channel.c for CHANNEL in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed May 18 22:56:25 2016 Victor Gouet
** Last update Fri Jun  3 11:04:05 2016 Victor Gouet
*/

#include "../lib/storage.h"
#include "../inc/server.h"

int		leave_channel(t_list *list,
			      char *name,
			      t_client *client)
{
  t_channel	*channel;
  t_elem	*elem;
  char		*msg;

  if ((channel = get_channel(name, list)) == NULL)
    {
      return (msg_to_client(client, ":%s 403 :No such channel\r\n"));
    }
  if ((elem = get_client_channel(name, client, list)) == NULL)
    return (send_msg_to_client(client, ERR_NOTONCHANNEL, 0));
  if ((msg = STRING(":%s!~%s PART %s\r\n", client->nick, SERVERNAME,
		    channel->name)) == NULL)
      return (0);
  bufferise(elem->client, msg);
  send_msg_to_channel(channel, elem->client, msg);
  erase_client_to_channel(channel, elem, list);
  return (0);
}
