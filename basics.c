/*
** basics.c for basics in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Thu Mar  5 12:03:53 2015 Steven Challe
** Last update Sat Aug 29 09:00:59 2015 Steven Challe
*/

#include "server.h"

int	error_exit(char *str)
{
  write(1, str, strlen(str));
  return (-1);
}

int	receive_msg(int client_sock, char *buff, struct sockaddr_in client)
{
  int	red;

  if (!(red = read(client_sock, buff, 1024)))
    {
      write(1, "Transmission from ", 18);
      write(1, inet_ntoa(client.sin_addr), strlen(inet_ntoa(client.sin_addr)));
      write(1, " ended.\n" ,8);
      return (-1);
    }
  buff[red] = '\0';
  return (0);
}

char	**fill_commands(char **arg_commands)
{
  int	k;

  if (!(arg_commands = malloc(sizeof(char *) * 4)))
    return (NULL);
  k = 0;
  if (!(arg_commands[k++] = strdup("cd")))
    return (NULL);
  if (!(arg_commands[k++] = strdup("get")))
    return (NULL);
  if (!(arg_commands[k++] = strdup("put")))
    return (NULL);
  arg_commands[k] = NULL;
  return (arg_commands);
}

char	*get_arg(char *buff)
{
  char	*arg;
  int	k;
  int	w;

  if (!(arg = malloc(sizeof(char) * (strlen(buff) - 3))))
    {
      error_exit("ERROR: malloc failed.\n");
      return (NULL);
    }
  k = 0;
  while (buff[k] && buff[k] != '\n' && buff[k] != '\r' && buff[k] != ' ')
    k++;
  k++;
  w = 0;
  while (buff[k] && buff[k] != '\n' && buff[k] != '\r')
    arg[w++] = buff[k++];
  arg[w] = '\0';
  return (arg);
}

int		file_len(char *file)
{
  struct stat	st;

  if (stat(file, &st) == -1)
    return (error_exit("ERROR: stat failed.\n"));
  return (st.st_size);
}
