/*
** send_to_client.c for SEND in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Thu May 26 15:04:20 2016 Victor Gouet
** Last update Fri Jun  3 11:03:16 2016 Victor Gouet
*/

#include <strings.h>
#include <stdarg.h>
#include "../inc/server.h"

static void	put_string(char *buffer, int *idx, va_list *ap)
{
  int		i;
  char		*str;

  str = va_arg(*ap, char *);
  i = 0;
  while (str && str[i])
    {
      buffer[*idx] = str[i++];
      (*idx)++;
    }
}

int	        msg_to_client(t_client *client,
			      char *format, ...)
{
  va_list	ap;
  char		buffer[4096];
  int		idx;

  va_start(ap, format);
  idx = 0;
  bzero(buffer, sizeof(buffer));
  while (*format)
    {
      if (*format == '%' && *(format + 1) == 's')
	{
	  put_string(buffer, &idx, &ap);
	  format = format + 1;
	}
      else
	{
	  buffer[idx++] = *format;
	}
      format = format + 1;
    }
  bufferise(client, buffer);
  return (0);
}

int		msg_not_enough_param(t_client *client,
				     char *command)
{
  return (msg_to_client(client, ":%s 461 %s :%s", SERVERNAME, command,
			"Not enough parameters\r\n"));
}

int		msg_not_register(t_client *client,
				 char *command)
{
  return (msg_to_client(client, ":%s 451 %s :%s", SERVERNAME, command,
			"You have not registered\r\n"));
}
