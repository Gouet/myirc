/*
** on_join_boucle.c for JOIN  in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May 30 11:54:42 2016 Victor Gouet
** Last update Mon May 30 11:56:16 2016 Victor Gouet
*/

#include "../inc/server.h"

void	on_join_gestion(t_client *client,
			t_elem *tmp)
{
  while (tmp)
    {
      msg_to_client(client, "%s%s", tmp->client->nick, !tmp->next
		    ? CRLF : " ");
      tmp = tmp->next;
    }
}
