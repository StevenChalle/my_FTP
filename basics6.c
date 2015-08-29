/*
** basics6.c for yo in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Mon Jun 22 17:16:21 2015 Steven Challe
** Last update Fri Jul 10 14:14:07 2015 Steven Challe
*/

#include "server.h"

char	*twenty_digits(char number[20])
{
  char	tmp[20];
  int	k;
  int	o;

  k = 0;
  while(number[k])
    {
      tmp[k] = number[k];
      k++;
    }
  tmp[k] = 0;
  k = 0;
  while (k != 20 - ((int)strlen(tmp) + 1))
    number[k++] = '0';
  o = 0;
  while (tmp[o])
    number[k++] = tmp[o++];
  number[k] = 0;
  return (number);
}

char	**fill_error_tab(char **error_msg)
{
  int	k;

  if (!(error_msg = malloc(sizeof(char*) * 22)))
    return (NULL);
  k = 0;
  if (!(error_msg[k++] = strdup("230\n")))
    return (NULL);
  if (!(error_msg[k++] = strdup(" User logged in, proceed.\r\n")))
    return (NULL);
  return (error_msg);
}

int	setsock(struct sockaddr_in *server, socklen_t *server_len, char **argv)
{
  int	sock;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  server->sin_family = AF_INET;
  server->sin_port = htons(atoi(argv[2]));
  server->sin_addr.s_addr = inet_addr(argv[1]);
  *server_len = sizeof(*server);
  return (sock);
}

char	*clean_command(char *buff)
{
  char	tmp[250];
  int	k;
  int	w;

  k = 0;
  w = 0;
  while (buff[k] == ' ')
    k++;
  while (buff[k])
    tmp[w++] = buff[k++];
  tmp[w] = 0;
  return (tmp);
}
