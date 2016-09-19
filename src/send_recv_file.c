/*
** send_recv_file.c for  in /home/saurs_f/PSU_2015_myirc
**
** Made by Saursinet
** Login   <saurs_f@epitech.net>
**
** Started on  Thu Jun  2 12:38:35 2016 Saursinet
** Last update Thu Jun  2 23:59:21 2016 Saursinet
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include "server.h"
#include "prototypes.h"

int	send_file(__attribute__((__unused__))int fd, char *str, t_user *user)
{
  char	tmp[4096];
  char	*file;
  char	*ip;

  if ((user->server_fd = create_server(0)) == -1)
    return (-1);
  bzero(tmp, 4096);
  strtok(str, " ");
  file = strtok(NULL, " ");
  sprintf(tmp, "PRIVMSG %s {file=%s, ip=%s, port=%d}\r\n",
	  file == NULL ? "" : file,
	  (ip = strtok(NULL, " ")) == NULL ? "" : ip,
	  take_addr(NULL),
	  take_ip(user->server_fd));
  printf("[%s]\n", tmp);
  user->file = strdup(ip);
  send_msg_to_server(user, tmp, 0);
  return (0);
}

int		take_fd_from_client(int *fd, __attribute__((__unused__))t_user *user)
{
  int		fd_tmp;
  int		fd_save;
  socklen_t	size;
  struct sockaddr_in	s_in;

  size = sizeof(s_in);
  fd_save = accept(*fd, (struct sockaddr *)&s_in, &size);
  fd_tmp = *fd;
  *fd = fd_save;
  return (fd_tmp);
}

int	send_complete(t_user *user)
{
  int	fd_tmp;
  int	fd_file;
  struct stat	stat_file;

  printf("before send\n");
  fd_tmp = take_fd_from_client(&user->server_fd, user);
  if (fd_tmp == -1 ||
      (user->file && (fd_file = open(user->file, O_RDONLY)) == -1) ||
      fstat(fd_file, &stat_file) == -1 ||
      sendfile(user->server_fd,
	       fd_file, NULL, stat_file.st_size) == -1)
    return (fprintf(stderr, "Cannot send\n"), -1);
  printf("after send\n");
  close(user->server_fd);
  close(fd_tmp);
  user->server_fd = -1;
  return (0);
}

int			recv_file(int fd, char *str, t_user *user)
{
  char			tmp[4096];
  int			fd_file;
  int			r;
  char			buff[4096];
  char			*name;
  t_struct_socket	sock;

  if (sock.port = user->port, bzero(tmp, 4096), !user->ip)
    return (0);
  strtok(str, " ");
  sprintf(tmp, "PRIVMSG %s ready to connect\r\n",
	  (name = strtok(NULL, " ")) == NULL ? "" : name);
  send_msg_to_server(user, tmp, 0);
  init_client_socket(&sock, user->ip);
  if (user->file == NULL || sock.fd == -1 ||
      (fd_file = open(user->file, O_WRONLY | O_CREAT, 0666)) == -1)
    {
      close(user->client_fd);
      return (fprintf(stderr, "Failed to send\n"), 0);
    }
  while ((r = read(sock.fd, buff, 4096)) > 0)
    write(fd_file, buff, r);
  close(sock.fd);
  close(fd_file);
  return (basic_answer(fd, str, user), 0);
}

int	get_ip_and_port(char *str, t_user *user)
{
  char	*tmp;

  printf("Serv answer :[%s]\n", str);
  strtok(str, "=");
  user->file = strdup(strtok(NULL, ","));
  strtok(NULL, "=");
  user->ip = strdup(strtok(NULL, ","));
  strtok(NULL, "=");
  user->port = atoi((tmp = strtok(NULL, ",")) == NULL ? "" : tmp);
  printf("%s\n", user->ip);
  return (0);
}
