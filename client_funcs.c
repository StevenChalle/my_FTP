/*
** client_funcs.c for cleint in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Sun Mar  8 23:05:53 2015 Steven Challe
** Last update Wed Jul  8 12:54:50 2015 Steven Challe
*/

#include "client.h"

int	receive_file(int sock, char *file_name)
{
  int	file_fd;
  char	*content;
  char  answer[120];
  char	filelen[20];
  int	red;

  red = read(sock, answer, 54);
  answer[red] = '\0';
  write(1, answer, strlen(answer));
  if (!strncmp(answer, "904", 3))
    return (-1);
  if ((file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    return (error_exit("ERROR: open file failed.\n"));
  red = read(sock, filelen, 20);
  filelen[red] = '\0';
  if (!(content = malloc(sizeof(char) * atol(filelen))))
    return (-1);
  red = read(sock, content, atol(filelen));
  content[red] = '\0';
  write(file_fd, content, strlen(content));
  red = read(sock, answer, 109);
  answer[red] = '\0';
  write(1, answer, strlen(answer));
  close(file_fd);
  return (0);
}

int	send_file(int sock, char *file_name)
{
  int	file_fd;
  char	*content;
  char	answer[120];
  char	number[20];
  int	red;
  int	done;

  if ((file_fd = open(file_name, O_RDONLY)) == -1)
    return (-1);
  if (!(content = malloc(sizeof(char) * file_len(file_name))))
    return (-1);
  if (send_msg(sock, "STOR", file_name, &done) == - 1)
    return (error_exit("ERROR: allocation failed.\n"));
  red = read(file_fd, content, file_len(file_name));
  content[red] = 0;
  red = read(sock, answer, 54);
  answer[red] = '\0';
  write(1, answer, strlen(answer));
  write(sock, itoa_like(file_len(file_name), number, 10), get_int_length(file_len(file_name)));
  write(sock, content, strlen(content));
  red = read(sock, answer, 108);
  answer[red] = '\0';
  write(1, answer, strlen(answer));
  close(file_fd);
  return (0);
}

int	receive_ls(int sock)
{
  char	buff[120];
  char	msglen[20];
  char	*ls;
  int	red;

  red = read(sock, buff, 54);
  buff[red] = 0;
  write(1, buff, strlen(buff));
  memset(buff, 0, strlen(buff));
  red = read(sock, msglen, 20);
  msglen[red] = '\0';
  if (!(ls = malloc(sizeof(char) * atol(msglen))))
    return (-1);
  red = read(sock, ls, atol(msglen));
  ls[red] = '\0';
  write(1, ls, strlen(ls));
  red = read(sock, buff, 108);
  buff[red] = '\0';
  write(1, buff, strlen(buff));
  return (0);
}
