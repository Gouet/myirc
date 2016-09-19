/*
** main_client.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 16 18:31:47 2016 Saursinet
** Last update Fri Jun  3 23:51:39 2016 Saursinet
*/

#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

int	init_sdl(t_sdl *sdl_struct)
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
      (sdl_struct->window =
       SDL_CreateWindow("Client myIrc",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_SHOWN)) == NULL ||
      (sdl_struct->renderer =
       SDL_CreateRenderer(sdl_struct->window, -1,
      			  SDL_RENDERER_ACCELERATED)) == NULL ||
      TTF_Init() == -1)
    {
      fprintf(stderr, "SDL failed to load\n");
      return (1);
    }
  if (SDL_SetRenderDrawColor(sdl_struct->renderer, 180, 180, 180, 0) == -1 ||
      SDL_RenderClear(sdl_struct->renderer) == -1)
    return (1);
  return (0);
}

int		SDL_part(t_sdl *sdl_struct)
{
  SDL_Rect	pos_client;
  SDL_Rect	pos_channel;

  pos_client.x = -40;
  pos_client.y = -80;
  pos_client.h = 250;
  pos_client.w = 430;
  pos_channel.x = (WIDTH / 4) * 3;
  pos_channel.y = -30;
  pos_channel.h = 280;
  pos_channel.w = 450;
  if (init_sdl(sdl_struct) == 1 || draw_boxes(sdl_struct, 1) == 1 ||
      draw_list_boxe(sdl_struct, 2) == 1 ||
      load_button(sdl_struct,
      		  "./ressources/client_list.png", pos_client) == 1 ||
      load_button(sdl_struct,
      		  "./ressources/channel_list.png", pos_channel) == 1)
    return (1);
  if ((sdl_struct->police = TTF_OpenFont("ressources/Calibri.ttf", 20)) == NULL)
    return (fprintf(stderr, "Failed to load police\n"), 1);
  memset(&sdl_struct->couleurNoire, 0, sizeof(SDL_Color));
  memset(&sdl_struct->couleurBlanche, 255, sizeof(SDL_Color));
  TTF_SetFontHinting(sdl_struct->police, TTF_HINTING_LIGHT);
  SDL_RenderPresent(sdl_struct->renderer);
  return (0);
}

void			use_select(char *answer, int *error, fd_set readfds,
				   t_user *user)
{
  struct timeval	timeout;
  int			opt;

  FD_ZERO(&readfds);
  FD_SET(0, &readfds);
  if (opt = 0, user->sock.fd != -1)
    FD_SET(user->sock.fd, &readfds);
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  if (select(user->sock.fd == -1 ?
	     3 : user->sock.fd + 1, &readfds, NULL, NULL, &timeout) == -1)
    *error = 0;
  else
    {
      if (FD_ISSET(0, &readfds))
	answer = get_next_line(0);
      if (user->sock.fd != -1 && FD_ISSET(user->sock.fd, &readfds))
	{
	  *error = (answer = recv_msg_from_server(user)) == NULL ? 1 : 0;
	  if (opt = 1, answer && strlen(answer) >= 1)
	    if (answer[strlen(answer) - 1] == '\r')
	      answer[strlen(answer) - 1] = 0;
	}
      check_answer(answer, user, opt);
    }
}

int	use_graphic_select(char *answer, int *error, fd_set readfds, t_user *user)
{
  char	*tmp;

  user->position.w = 200;
  user->position.h = 20;
  user->position.x = WIDTH / 4;
  while (SDL_PollEvent(&user->sdl_struct.event))
    {
      SDL_GetKeyboardState(NULL);
      if (user->sdl_struct.event.window.event == SDL_WINDOWEVENT_CLOSE ||
	  (user->sdl_struct.event.type == SDL_KEYDOWN &&
	   user->sdl_struct.event.key.keysym.sym == SDLK_ESCAPE))
	return (*error = 1);
      if ((tmp = catch_text(user->str, &user->nb,
			    &user->sdl_struct, user->position)))
	check_answer(tmp, user, 0);
      use_select(answer, error, readfds, user);
      print_history(user);
    }
  return (0);
}

int			main(int ac, char **av)
{
  char			*answer;
  t_user		user;
  int			error;
  fd_set		readfds;

  if (init_all_variables(&user, &error),
      ac == 2 && strcmp(av[1], "--graphics") == 0)
    {
      SDL_part(&user.sdl_struct);
      user.graphic_mode = 1;
    }
  while (answer = NULL, !error)
    {
      if (user.graphic_mode == 1)
  	use_graphic_select(answer, &error, readfds, &user);
      else
  	use_select(answer, &error, readfds, &user);
    }
  if (clear_dico(&user.dico), user.graphic_mode == 1)
    {
      SDL_DestroyWindow(user.sdl_struct.window);
      SDL_Quit();
    }
  return (0);
}
