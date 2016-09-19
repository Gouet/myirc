/*
** server.h for SERVER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Mon May 16 18:41:46 2016 Victor Gouet
** Last update Fri Jun  3 10:37:44 2016 Victor Gouet
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <unistd.h>
# include <netinet/in.h>
# include "client.h"

# define COMMAND_SIZE		11
# define DELETE			1
# define NOTHING		0

# define IS_NO_CHANNEL(list, channel)	list->begin == channel

# define CRLF			"\r\n"
# define ERR_NONICKNAMEGIVEN	"431 :No nickname given"CRLF
# define ERR_NICKNAMEINUSE	"433 :Nickname is already in use"CRLF
# define ERR_NICKCOLLISION	"436 :Nickname collision KILL"CRLF
# define ERR_ERRONEUSNICKNAME 	"432 :Erroneus nickname"CRLF
# define ERR_NEEDMOREPARAMS	"461 :Not enough parameters"CRLF
# define ERR_NOSUCHCHANNEL	"403 :No such channel"CRLF
# define RPL_NOTOPICNBR		"331 "
# define RPL_NOTOPIC		" :No topic is set"CRLF
# define RPL_ENDOFNAMES		"366 :End of /Nameslist"CRLF
# define ERR_NOTONCHANNEL	"442 : You're not on that channel"CRLF
# define RPL_NOUSERS		"395 :Nobody logged in"CRLF
# define RPL_USERSSTART		"392 :UserID Terminal Hôte"CRLF
# define RPL_ENDOFUSERS 	"394 :End of users"CRLF
# define RPL_LISTSTART		"321 :Channel :Users Name"CRLF
# define RPL_LISTEND		"323 :End of /LIST"CRLF
# define ERR_NORECIPIENT	"411 :No recipient given"CRLF
# define ERR_NOTEXTTOSEND	"412 :No text to send"CRLF
# define ERR_NOSUCHNICK		"401 :No such nick/channel"CRLF
# define ERR_NOTREGISTERED	"451 :You have not registered"CRLF
# define ERR_UNKNOWNCOMMAND	"421 :Unknown command"CRLF
# define ERR_UNKNOWNCLIENT	"501 :Unwnown client"CRLF
# define SERVERNAME		"VictorServer"
# define DEFAUTLUSERPORT	"567"

typedef enum			CHANNEL
{
  DEFAULT,
  NONE
}			        CHANNEL;

typedef struct			s_command
{
  char				*command;
  char				*case_command;
  int				(*fptr)();
}				t_command;

typedef struct			s_elem
{
  struct s_elem			*next;
  t_client			*client;
}				t_elem;

typedef struct			s_channel
{
  char				*name;
  char				*topic;
  t_elem			*begin;
  t_elem			*end;
  int				max_fd;
  int				ref_fd;
  struct s_channel		*next;
}				t_channel;

typedef struct			s_list
{
  t_channel			*begin;
  t_channel			*end;
  int				max_fd;
  int				ref_fd;
}				t_list;

/*
**	on_join_boucle.c
*/

void	on_join_gestion(t_client *client,
			t_elem *tmp);

/*
**	names_gestions.c
*/

void		send_names_command(char *name, char **tab, t_elem *elem,
				   t_list *list);

/*
**	send_to_client.c
*/

int		msg_not_register(t_client *client,
				 char *command);
int	        msg_to_client(t_client *client,
			      char *format, ...);
int		msg_not_enough_param(t_client *client,
				     char *command);

/*
**	TransferFunctions.c
*/

char	*take_addr(char *save);
int	take_ip(int);

/*
**	command_gestion_user.c
*/

int	on_user(t_list *list, t_elem *elem, char **tab, char *);
int	on_quit(t_list *list, t_elem *elem, char **tab, char *);

/*
**	leave_channel.c
*/

int		leave_channel(t_list *list,
			      char *name,
			      t_client *client);

/*
**      client_info.c
*/

int		get_duplicated_client(t_list const *list,
				      t_client const *client);
int		is_client_already_managed(t_list const *list,
					  t_elem const *elem_client);
int		is_client_already_on_channel(t_channel const *channel,
					     t_client const *client);
t_elem		*get_client_from_name(t_list const *list,
				      char const *name);
int		is_authentificated(t_client *client);

/*
**	command_gestion_client.c
*/

int		on_names(t_list *list, t_elem *elem, char **tab);
int	        on_list(t_list *list, t_elem *elem, char **tab);
int		on_users(t_list *list, t_elem *elem, char **tab);
int		on_nick(t_list *list, t_elem *elem, char **tab);

/*
**	command_gestion_channel.c
*/

int	        on_join(t_list *list, t_elem *elem, char **tab);
int		on_part(t_list *list, t_elem *elem, char **tab);

/*
**	command_gestion_send.c
*/

char		*get_message(char *tab, char *buffer);
int	        on_send_priv(t_list *list, t_elem *elem,
			     char **tab, char *);
int		on_send_file(t_list *list, t_elem *elem, char **tab);
int		on_accept_file(t_list *list, t_elem *elem, char **tab);
void		send_client_name_to_client(t_client *client,
					   char *username);

/*
**	get_data.c
*/

int		contain_string(char const *s1, char const *s2);
void		delete_command(char **command, char *buffer);
char		**split(char *str, char carac);
char		**str_to_word_tab(char *buffer);

/*
**	channels_gestion.c
*/

t_channel	*get_channel(char const *channel_name,
			     t_list const *list);
t_elem		*get_client_channel(char const *channel_name,
				    t_client const *client,
				    t_list const *list);
int		channels_gestion(t_list *channel_list, fd_set *fds);
int		manage_channel(t_list *channel_list, fd_set *fds);
void		display_list(t_list const *channel_list);

/*
**	erase_client.c
*/

void		set_max_fd_on_list_channel(t_list *list_channel);
void	        set_max_fd_on_channel(t_channel *channel);
t_elem		*erase_client_to_channel(t_channel *channel,
					 t_elem *client,
					 t_list *);
void		*erase_client_to_the_server(t_client *client,
					    t_list *list);
/*
**	channel_lists_gestion.c
*/

void		new_lists(t_list *list, int const server);
t_channel	*new_channel(t_list *list);
void		delete_all_clients(t_channel *channel, t_list *);
t_channel	*delete_channel(t_list *list,
				t_channel *channel);
t_elem		*new_clients(t_list *list,
			     t_client *client,
			     CHANNEL type);

/*
**	clients_gestion.c
*/

int	clients_gestion(t_channel *channel, fd_set *fds,
			t_list *list);
int	send_msg_to_clients(t_channel *channel,
			    t_elem const *ref,
			    char const *msg,
			    t_list *list_channel);
int	send_msg_to_channel(t_channel *channel,
			    t_client const *ref,
			    char *msg);

/*
**	server.c
*/

int		create_server(int const port);
int		run_server(int const server);

/*
**	server_connection.c
*/

int			get_fd_with_protocol_name(char const *protocole_name);
void			close_socket_fd(int const fd);
int		        bind_socketaddr(int const fd, int const port);
int			create_queue(int const fd, int const size);
t_client		*connect_to_socket(int const fd, char const *ip,
					   int const port);

#endif
