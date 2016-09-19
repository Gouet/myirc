/*
** client.h for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May 16 18:42:53 2016 Victor Gouet
** Last update Fri Jun  3 10:17:42 2016 Victor Gouet
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <unistd.h>
# include <netinet/in.h>
# include "ring_buffer.h"

typedef struct			s_client
{
  int				fd;
  char				*ip;
  char				*nick;
  char				*username;
  char				*hostname;
  char				*servername;
  char				*realname;
  char				*actual_file;
  char				*actual_user;
  t_ring_buffer			ring;
  struct sockaddr_in		s_in_client;
}				t_client;

void	bufferise(t_client *client, char *data);
void	flush(t_client *client);

/*
**	client_connection.c
*/

void			delete_client(t_client *client);
t_client		*get_client_from_server(int const fd_server);
int			send_msg_to_client(t_client const *client,
					   char const *msg, int flags);
char			*recv_msg_from_client(t_client const *client);
int			send_file_to_client(t_client const *client,
					    char const *file);

#endif
