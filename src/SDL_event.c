/*
** SDL_event.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 23 20:40:17 2016 Saursinet
** Last update Thu Jun  2 23:56:10 2016 Saursinet
*/

#include "server.h"
#include "prototypes.h"

char	*catch_validate(char *str, int *nb, t_sdl *sdl, SDL_Rect pos)
{
  char	*tmp;

  tmp = NULL;
  pos.y = HEIGHT - 70;
  pos.w = -1;
  if (sdl->event.key.keysym.sym == 8)
    {
      if (*nb != 0)
	{
	  --*nb;
	  str[*nb] = 0;
	  if (*nb == 0)
	    print_string(" ", sdl, pos, sdl->couleurNoire);
	  else
	    print_string(str, sdl, pos, sdl->couleurNoire);
	}
    }
  else if (sdl->event.key.keysym.sym == 13)
    {
      tmp = strdup(str);
      str[0] = 0;
      *nb = 0;
      print_string(" ", sdl, pos, sdl->couleurNoire);
    }
  return (tmp);
}

char	*catch_text(char *str, int *nb, t_sdl *sdl, SDL_Rect pos)
{
  char	*tmp;

  tmp = NULL;
  pos.y = HEIGHT - 70;
  pos.w = -1;
  if (sdl->event.type == SDL_TEXTINPUT && *nb < 40)
    {
      strcat(str, sdl->event.text.text);
      ++*nb;
      print_string(str, sdl, pos, sdl->couleurNoire);
    }
  else if (sdl->event.type == SDL_KEYDOWN)
    tmp = catch_validate(str, nb, sdl, pos);
  return (tmp);
}

int		create_server(int const port)
{
  int		server_fd;

  if ((server_fd = get_fd_with_protocol_name("TCP")) == -1)
    {
      write(2, "get_fd_with_protocol_name failed\n", 33);
      return (-1);
    }
  if (bind_socketaddr(server_fd, port) == -1)
    {
      write(2, "bind_socketaddr failed\n", 23);
      return (close_socket_fd(server_fd), -1);
    }
  if (create_queue(server_fd, 118) == -1)
    {
      write(2, "create_queue failed\n", 20);
      return (close_socket_fd(server_fd), -1);
    }
  return (server_fd);
}
