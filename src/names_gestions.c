/*
** names_gestions.c for NAMES in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri May 27 15:44:28 2016 Victor Gouet
** Last update Fri May 27 16:29:42 2016 Victor Gouet
*/

#include <string.h>
#include <strings.h>
#include "../inc/server.h"

void		send_names_command(char *name, char **tab, t_elem *elem,
				   t_list *list)
{
  t_channel	*channel;
  t_elem	*tmp;

  if (tab[1])
    {
      strcpy(name, tab[1]);
      if ((channel = get_channel(tab[1], list)) == NULL)
        return ;
      tmp = channel->begin;
      msg_to_client(elem->client, ":%s 353 %s = %s :",
		    SERVERNAME, elem->client->nick, channel->name);
      while (tmp)
	{
	  if (tmp->client->nick)
	    msg_to_client(elem->client, "%s%s", elem->client->nick,
			  !elem->next ? "\r\n" : " ");
	  tmp = tmp->next;
	}
    }
}
