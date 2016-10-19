/*
** get_next_line.c for get_next_line in /home/khoual_s/Documents/Rendu/GetNextLine
** 
** Made by Khoualdia Sabri
** Login   <khoual_s@pc-sabri-khoualdia>
** 
** Started on  Mon Jan 11 21:45:51 2016 Khoualdia Sabri
** Last update Thu Mar  3 19:16:41 2016 Khoualdia Sabri
*/

#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  while (src[i])
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (dest);
}

char    *my_realloc(char *ptr, size_t size)
{
  char *ptr2;

  if ((ptr2 = malloc(sizeof(char) * (my_strlen(ptr) + size + 1))) == NULL)
    return (NULL);
  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
    free(ptr);
  my_strcpy(ptr2, ptr);
  return (ptr2);
}

int	get_char(int fd, char *c)
{
  static int	i = 0;
  static char	buffer[READ_SIZE];
  static int	rs = READ_SIZE;

  if (i >= rs || i == 0)
    {
      i = 0;
      if ((rs = read(fd, buffer, READ_SIZE)) == -1)
	  return (-1);
    }
  if (rs == 0 || buffer[i] == '\n')
    *c = '\0';
  else
    *c = buffer[i];
  i++;
  return (rs);
}

char	*get_next_line(const int fd)
{
  char	*buffer;
  int	i;
  int	rs;

  i = 0;
  rs = 0;
  if ((buffer = malloc(sizeof(char) * READ_SIZE + 1)) == NULL)
    return (NULL);
  rs = get_char(fd, &buffer[i]);
  if (rs == 0)
    return (NULL);
  while (buffer[i])
    {
      if (buffer[i] == '\0')
	if ((buffer = my_realloc(buffer, i + READ_SIZE)) == NULL)
	  return (NULL);
      rs = get_char(fd, &buffer[++i]);
    }
  buffer[i + 1] = buffer[rs + 1];
  return (buffer);
}
