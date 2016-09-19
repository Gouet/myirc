/*
** TransferFunctions.c for my_ftp in /home/saurs_f/PSU_2015_myftp/src/
**
** Made by Florian Saurs
** Login   <saurs_f@epitech.eu>
**
** Started on  Mon May  2 16:59:37 2016 Florian Saurs
** Last update Thu Jun  2 15:55:25 2016 Saursinet
*/

#include <sys/types.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include "../inc/server.h"

char			*take_addr(char *save)
{
  struct ifaddrs	*ipstruct;
  struct ifaddrs	*tmp;
  char			host[NI_MAXHOST];

  if (getifaddrs(&ipstruct) == -1)
    return (save);
  tmp = ipstruct;
  while (tmp)
    {
      if (tmp->ifa_addr->sa_family == AF_INET)
	{
	  if (getnameinfo(tmp->ifa_addr, sizeof(struct sockaddr_in), host,
			  NI_MAXHOST, NULL, 0, NI_NUMERICHOST) != 0)
	    return (save[0] = -1, save);
	  if (!save || strcmp("127.0.0.1", save) == 0)
	    {
	      if (save)
		free(save);
	      save = strdup(host);
	    }
	}
      tmp = tmp->ifa_next;
    }
  return (freeifaddrs(ipstruct), save);
}

int			take_ip(int fd)
{
  socklen_t		len;
  struct sockaddr_in	s_in_client;

  if (len = sizeof(s_in_client),
      getsockname(fd,
		  (struct sockaddr *)&s_in_client, &len) == -1)
    return (printf("fail\n"), 0);
  else
    return (ntohs(s_in_client.sin_port));
}
