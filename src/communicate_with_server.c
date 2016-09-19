/*
** communicate_with_server.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Tue May 24 11:51:04 2016 Saursinet
** Last update Tue May 24 15:58:15 2016 Saursinet
*/

#include <unistd.h>
#include "struct.h"

char		*recv_msg_from_server(t_user const *client)
{
  int		re;
  char		*buffer;
  char		str[4097];
  int		size;
  int		i;

  if ((buffer = malloc(4097)) == NULL)
    return (NULL);
  size = 0;
  while ((re = read(client->sock.fd, str, 1)) > 0)
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

int	send_msg_to_server(t_user const *client,
			   char const *msg,
			   int flags)
{
  int	len;
  int	ret;
  int	ref;

  len = 0;
  ref = strlen(msg);
  while (len < ref)
    {
      ret = send(client->sock.fd, (msg + len), ref - len, flags);
      if (ret <= 0)
	return (-1);
      len = len + ret;
    }
  return (0);
}
