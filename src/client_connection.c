/*
** client_connection.c for CLIENT CONNECTION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 11:15:59 2016 Victor Gouet
** Last update Fri Jun  3 10:33:02 2016 Victor Gouet
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/server.h"

t_client		*get_client_from_server(int const fd_server)
{
  t_client		*client;
  socklen_t		s_in_size;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  s_in_size = sizeof(client->s_in_client);
  if ((client->fd = accept(fd_server,
			   (struct sockaddr *)&(client->s_in_client),
			   &s_in_size)) == -1)
    {
      free(client);
      return (NULL);
    }
  client->ip = inet_ntoa(client->s_in_client.sin_addr);
  if (strcmp(client->ip, "127.0.0.1") == 0)
    client->ip = take_addr(NULL);
  client->nick = NULL;
  client->username = NULL;
  client->hostname = NULL;
  client->servername = NULL;
  client->realname = NULL;
  client->actual_file = NULL;
  reset(&(client->ring));
  return (client);
}

void			delete_client(t_client *client)
{
  if (close(client->fd) == -1)
    {
      write(2, "client close failed\n", 20);
    }
  free(client);
}

int			send_msg_to_client(t_client const *client,
					   char const *msg,
					   int flags)
{
  int			len;
  int			ret;
  int			ref;

  len = 0;
  if (msg == NULL)
    return (0);
  ref = strlen(msg);
  while (len < ref)
    {
      ret = send(client->fd, (msg + len), ref - len,
		 flags | MSG_NOSIGNAL);
      if (ret <= 0)
	return (-1);
      len = len + ret;
    }
  return (0);
}

char		*recv_msg_from_client(t_client const *client)
{
  int		re;
  char		*buffer;
  char		str[4097];
  int		size;
  int		i;

  if ((buffer = malloc(4097)) == NULL)
    return (NULL);
  size = 0;
  while ((re = read(client->fd, str, 1)) > 0)
    {
      str[re] = '\0';
      i = 0;
      while (str[i] != '\0')
	{
	  buffer[size++] = str[i] == '\n' ? '\0' : str[i];
	  ++i;
	  if ((size >= 2 && buffer[size - 1] == '\0' &&
	       buffer[size - 2] == '\r') || size >= 4097)
	    return (buffer);
	}
    }
  free(buffer);
  return (NULL);
}
