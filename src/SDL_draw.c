/*
** SDL_draw.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 23 17:13:41 2016 Saursinet
** Last update Sat Jun  4 01:27:37 2016 Saursinet
*/

#include "prototypes.h"

int		draw_boxes(t_sdl *sdl_struct, int opt)
{
  SDL_Rect	history;
  SDL_Rect	textbox;

  history.x = WIDTH / 4;
  history.y = 20;
  history.h = HEIGHT - 110;
  history.w = WIDTH / 2;
  textbox.x = WIDTH / 4;
  textbox.y = history.h + history.y + 20;
  textbox.h = 50;
  textbox.w = WIDTH / 2;
  if (SDL_SetRenderDrawColor(sdl_struct->renderer, 0, 0, 0, 250) == -1 ||
      SDL_RenderFillRect(sdl_struct->renderer, &history) == -1)
    return (1);
  if (opt != 2 &&
      (SDL_SetRenderDrawColor(sdl_struct->renderer, 250, 250, 250, 250) == -1 ||
       SDL_RenderFillRect(sdl_struct->renderer, &textbox) == -1))
    return (1);
  return (0);
}

int		draw_list_boxe(t_sdl *sdl_struct, int opt)
{
  SDL_Rect	client;
  SDL_Rect	channel;

  client.x = 0;
  client.y = 20;
  client.h = HEIGHT - 110;
  client.w = WIDTH / 4;
  channel.x = (WIDTH / 4) * 3;
  channel.y = 20;
  channel.h = HEIGHT - 110;
  channel.w = WIDTH / 4;
  if ((opt == 0 || opt == 2) &&
      (SDL_SetRenderDrawColor(sdl_struct->renderer, 153, 0, 0, 0) == -1 ||
       SDL_RenderFillRect(sdl_struct->renderer, &client) == -1))
    return (1);
  if ((opt == 1 || opt == 2) &&
      (SDL_SetRenderDrawColor(sdl_struct->renderer, 153, 0, 0, 0) == -1 ||
       SDL_RenderFillRect(sdl_struct->renderer, &channel) == -1))
    return (1);
  return (0);
}

int	load_button(t_sdl *sdl_struct, char *path, SDL_Rect pos)
{
  SDL_Surface	*tmp;
  SDL_Surface	*tmp2;
  SDL_Texture	*bouton;

  if ((tmp = IMG_Load(path)) == NULL ||
      (tmp2 = SDL_ConvertSurface(tmp, tmp->format, 0)) == NULL ||
      (bouton =
       SDL_CreateTextureFromSurface(sdl_struct->renderer, tmp2)) == NULL)
    {
      fprintf(stderr, "Cannot load client image\n");
      return (1);
    }
  SDL_FreeSurface(tmp);
  SDL_RenderCopy(sdl_struct->renderer, bouton, NULL, &pos);
  return (0);
}

void		print_string(char *str, t_sdl *sdl, SDL_Rect pos, SDL_Color color)
{
  SDL_Surface	*texte;
  SDL_Texture	*texture;
  int		opt;

  if ((texte =
       TTF_RenderText_Blended(sdl->police, str, color)) == NULL ||
      (texture = SDL_CreateTextureFromSurface(sdl->renderer, texte)) == NULL)
    return ;
  SDL_FreeSurface(texte);
  opt = pos.w;
  if (pos.w == -1)
    draw_boxes(sdl, 0);
  pos.w = strlen(str) * 10;
  SDL_RenderCopy(sdl->renderer, texture, NULL, &pos);
  if (opt != -2)
    SDL_RenderPresent(sdl->renderer);
}

void	print_history(t_user *user)
{
  int	i;

  i = -1;
  user->position.y = 0;
  user->position.w = -2;
  draw_boxes(&user->sdl_struct, 2);
  while (user->position.y += 20, user->history[++i])
    print_string(user->history[i], &user->sdl_struct, user->position,
		 user->sdl_struct.couleurBlanche);
  i = -1;
  user->client_pos.y = 130;
  while (user->client_pos.y += 20, user->client_list[++i])
    print_string(user->client_list[i], &user->sdl_struct, user->client_pos,
		 user->sdl_struct.couleurBlanche);
  user->channels_pos.y = 130;
  i = -1;
  while (user->channels_pos.y += 20, user->channel_list[++i])
    print_string(user->channel_list[i], &user->sdl_struct, user->channels_pos,
		 user->sdl_struct.couleurBlanche);
  SDL_RenderPresent(user->sdl_struct.renderer);
}
