/*
** main_server.c for SARSINET in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May 16 18:47:35 2016 Victor Gouet
** Last update Mon May 16 18:50:48 2016 Victor Gouet
*/

#include <stdlib.h>
#include <stdio.h>
#include "../inc/server.h"

int	main(int ac, char **av)
{
  int	fd_server;

  if (ac != 2)
    {
      fprintf(stderr, "Usage : %s port\n", av[0]);
      return (1);
    }
  if ((fd_server = create_server(atoi(av[1]))) == -1)
    return (-1);
  run_server(fd_server);
  return (0);
}
