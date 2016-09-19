/*
** get_next_line.c for get_next_line in /home/saurs_f/rendu/CPE_2014_get_next_line
**
** Made by Florian Saurs
** Login   <saurs_f@epitech.net>
**
** Started on  Fri Nov 21 14:33:39 2014 Florian Saurs
** Last update Mon May 23 14:08:54 2016 Saursinet
*/

#include <unistd.h>
#include <stdlib.h>

#define	BUFF_SIZE	4096

int	str_len(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != 0)
    i++;
  return (i);
}
char	*my_add_str(char *buff, char *dest, int *pos, int final)
{
  char	*tmp;
  int	i;
  int	j;
  int	len;

  len = str_len(dest);
  i = 0;
  j = 0;
  if ((tmp = malloc(final + len + 1)) == 0)
    return (NULL);
  while (i < len)
    {
      tmp[i] = dest[i];
      i++;
    }
  while (j < final)
    {
      tmp[i + j] = buff[*pos + j];
      j++;
    }
  tmp[i + j] = 0;
  if (dest != NULL)
    free(dest);
  *pos = *pos + final + 1;
  return (tmp);
}

char		*get_next_line(const int fd)
{
  static char	buff[BUFF_SIZE + 1];
  static int	pos;
  static int	limit;
  char		*str;
  int		final;

  final = 0;
  str = NULL;
  while (1)
    {
      if (pos >= limit)
	{
	  pos = 0;
	  final = 0;
	  if ((limit = read(fd, buff, BUFF_SIZE)) <= 0)
	    return (str);
	}
      if (buff[pos + final] == '\n')
	return (my_add_str(buff, str, &pos, final));
      if (pos + final == limit - 1)
	str = my_add_str(buff, str, &pos, final + 1);
      final++;
    }
}
