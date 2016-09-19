/*
** init_client_connection.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 23 17:30:21 2016 Saursinet
** Last update Sat Jun  4 01:25:31 2016 Saursinet
*/

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "prototypes.h"

void	init_all_variables(t_user *user, int *error)
{
  init_dico(&user->dico);
  user->sock.fd = -1;
  user->graphic_mode = 0;
  *error = 0;
  user->nb = 0;
  bzero(user->str, 41);
  user->history[0] = NULL;
  user->client_list[0] = NULL;
  user->channel_list[0] = NULL;
  user->ip = NULL;
  user->port = 0;
  user->server_fd = -1;
  user->client_fd = -1;
  user->client_pos.w = 200;
  user->client_pos.h = 20;
  user->client_pos.x = 20;
  user->channels_pos.w = 200;
  user->channels_pos.h = 20;
  user->channels_pos.x = 20 + 3 * WIDTH / 4;
}

int	init_socket(t_struct_socket *sock)
{
  sock->s_in.sin_family = AF_INET;
  sock->s_in.sin_port = htons(sock->port);
  sock->protocol_struct = getprotobyname("TCP");
  if (!sock->protocol_struct)
    return (fprintf(stderr, "Can't access to protocol ID.\n"));
  sock->fd = socket(AF_INET, SOCK_STREAM, sock->protocol_struct->p_proto);
  if (sock->fd == -1)
    return (fprintf(stderr, "Can't create the socket.\n"));
  return (0);
}

int	init_client_socket(t_struct_socket *sock, char *ip)
{
  if (ip == NULL)
    return (fprintf(stderr, "IP is NULL.\n"));
  sock->s_in.sin_addr.s_addr = inet_addr(ip);
  if (init_socket(sock) != 0)
    return (-1);
  if (connect(sock->fd, (struct sockaddr *)&sock->s_in,
	      sizeof(sock->s_in)) == -1)
    {
      if (close(sock->fd) == -1)
	return (fprintf(stderr, "Can't close the socket.\n"));
      return (fprintf(stderr, "Can't connect on the socket.\n"));
    }
  return (0);
}

char	*take_ip_from_str(char *str, t_struct_socket *sock)
{
  char	*tmp;
  char	*ip;
  char	*port;

  tmp = strdup(str);
  strtok(tmp, " ");
  ip = strdup((tmp = strtok(NULL, " ")) == NULL ? "" : tmp);
  port = strdup((tmp = strtok(NULL, " ")) == NULL ? "" : tmp);
  sock->port = atoi(port);
  free(port);
  return (ip);
}

int	connect_to_serv(int fd, char *str, t_user *user)
{
  if (fd == -1)
    {
      if (init_client_socket(&user->sock, take_ip_from_str(str, &user->sock)) != 0)
	return (user->sock.fd = -1, -1);
      send_msg_to_server(user, "NICK toto\r\n\
USER jackie michel jackie-michel jean-mich-mich\r\n", 0);
    }
  else
    printf("User already conencted\n");
  return (0);
}
