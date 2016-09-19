/*
** struct.h for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 23 14:46:15 2016 Saursinet
** Last update Sat Jun  4 00:47:27 2016 Saursinet
*/

#ifndef STRUCT_H_
# define STRUCT_H_

# include <netinet/in.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

typedef struct			s_struct_socket
{
  struct protoent		*protocol_struct;
  int				fd;
  struct sockaddr_in		s_in;
  int				port;
}				t_struct_socket;

typedef struct			s_dico
{
  char				*cmd[22];
  char				*serv[22];
  int				(*ptr[22])();
}				t_dico;

typedef struct			s_sdl
{
  SDL_Event			event;
  SDL_Renderer			*renderer;
  SDL_Window			*window;
  TTF_Font			*police;
  SDL_Color			couleurNoire;
  SDL_Color			couleurBlanche;
}				t_sdl;

typedef struct			s_user
{
  t_struct_socket		sock;
  SDL_Rect			position;
  SDL_Rect			client_pos;
  SDL_Rect			channels_pos;
  t_dico			dico;
  int				graphic_mode;
  t_sdl				sdl_struct;
  int				nb;
  char				str[41];
  char				*history[40];
  char				*client_list[31];
  char				*channel_list[31];
  int				server_fd;
  int				client_fd;
  char				*ip;
  int				port;
  char				*file;
}				t_user;

#endif /* !STRUCT_H_ */
