##
## Makefile for myftp in /home/saurs_f/PSU_2015_myftp
##
## Made by Saursinet
## Login   <saurs_f@epitech.net>
##
## Started on  Mon May  2 09:34:15 2016 Saursinet
## Last update Sat Jun  4 01:32:29 2016 Saursinet
##

CC		= gcc

RM		= rm -f

MAKEOBJ		= obj

CFLAGS		= -Wall -Wextra -W

LDFLAGS		= -lSDL2_image -lSDL2 -lSDL2_ttf

# DIRECTORIES PART

SRCDIR		= src/

OBJDIR		= obj/

INCDIR		= -I inc/

# SOURCE LIB STRING

LIBNAME		= libstringLib.a

LIBS		= lib/on_flag_bounded.c \
		  lib/on_flag_reverse.c \
		  lib/on_flag_strings.c \
		  lib/controller_flags.c \
		  lib/on_flag_char.c \
		  lib/on_flags_bits.c \
		  lib/storage.c \
		  lib/counts_size_bytes.c \
		  lib/on_flag_integer.c \
		  lib/on_flags_less.c \

# SOURCES PART

CLIENTSRCS	= main_client.c			\
		  get_next_line.c		\
		  dico.c			\
		  SDL_draw.c			\
		  init_client_connection.c	\
		  SDL_event.c			\
		  communicate_with_server.c	\
		  client_message.c		\
		  send_recv_file.c		\
		  server_connection.c		\
		  transfer_functions.c		\
		  add_history.c

SERVERSRCS	= main_server.c \
		  client_connection.c \
		  server.c \
		  server_connection.c \
		  clients_gestion.c \
		  channel_lists_gestion.c \
		  erase_client.c \
		  channels_gestion.c \
		  get_data.c \
		  command_gestion_send.c \
		  command_gestion_channel.c \
		  command_gestion_client.c \
		  client_info.c \
		  leave_channel.c \
		  command_gestion_user.c \
		  transfer_functions.c \
		  send_to_client.c \
		  names_gestions.c \
		  on_join_boucle.c \
		  ring_buffer.c \

# OBJS PART

CLIENTOBJS	= $(addprefix $(OBJDIR), $(CLIENTSRCS:.c=.o))

SERVEROBJS	= $(addprefix $(OBJDIR), $(SERVERSRCS:.c=.o))

OBJSLIB		= $(LIBS:.c=.o)

# BINARIES PART

SERVERNAME	= server

CLIENTNAME	= client

# RULES

all:
		@make --no-print-directory $(SERVERNAME)
		@make --no-print-directory $(CLIENTNAME)

$(OBJDIR)%.o:	$(SRCDIR)%.c
		@mkdir -p $(MAKEOBJ)
		$(CC) $(CFLAGS) -o $@ -c $< $(INCDIR)

$(CLIENTNAME): 	$(CLIENTOBJS)
		$(CC) $(CFLAGS) -o $(CLIENTNAME) $(CLIENTOBJS) $(LDFLAGS)

$(SERVERNAME): 	$(SERVEROBJS) $(OBJSLIB)
		ar rc $(LIBNAME) $(OBJSLIB)
		ranlib $(LIBNAME)
		$(CC) $(CFLAGS) -o $(SERVERNAME) $(SERVEROBJS) -L ./ -lstringLib

clean:
	$(RM) $(SERVEROBJS)
	$(RM) $(CLIENTOBJS)
	$(RM) $(OBJSLIB)

fclean: clean
	$(RM) $(SERVERNAME)
	$(RM) $(CLIENTNAME)
	$(RM) $(LIBNAME)

re:	fclean all

.PHONY:	all clean fclean re
