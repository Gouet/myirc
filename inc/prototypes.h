/*
** prototypes.h for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Mon May 23 14:47:49 2016 Saursinet
** Last update Sat Jun  4 00:10:19 2016 Saursinet
*/

#ifndef PROTOTYPES_H_
# define PROTOTYPES_H_

# include "struct.h"

# define ESCAPE		1

# define HEIGHT		900
# define WIDTH		1400

/*
**	get_next_line.c
*/

char	*get_next_line(int);

/*
**	dico.c
*/

int	init_dico(t_dico *);
void	clear_dico(t_dico *);

/*
**	main_client.c
*/

int	connect_to_serv(int fd, char *str, t_user *);
int	send_msg_to_server(t_user const *, char const *, int);
char	*recv_msg_from_server(t_user const *);
int	answer_serv(int, char *, t_user *);
int	basic_answer(int, char *, t_user *);

/*
**	SDL_draw.c
*/

int	draw_boxes(t_sdl *, int);
int	draw_list_boxe(t_sdl *, int);
int	init_sdl(t_sdl *);
int	load_button(t_sdl *, char *, SDL_Rect);
char	*deal_events(t_sdl *);

/*
**	SDL_event.c
*/

void	print_string(char *, t_sdl *, SDL_Rect, SDL_Color);
void	write_to_serv(char *);
char	*catch_text(char *, int *, t_sdl *, SDL_Rect);
void	print_history(t_user *);

/*
**	client_message.c
*/

void	init_all_variables(t_user *, int *);
int	check_answer(char *, t_user *, int);

/*
**	send_recv_file.c
*/

int	send_file(int, char *, t_user *);
int	recv_file(int, char *, t_user *);
int	get_ip_and_port(char *, t_user *);
int	send_complete(t_user *);
int	init_client_socket(t_struct_socket *, char *);

/*
**	add_history.c
*/

int	channel_list(int, char *, t_user *);
int	user_list(int, char *, t_user *);

#endif /* !PROTOTYPES_H_ */
