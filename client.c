/*
** client.c for sockets in /home/challe_s/rendu/PSU_2015_myftp/tp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Wed Mar  4 10:58:39 2015 Steven Challe
** Last update Sat Aug 29 09:04:37 2015 Steven Challe
*/

#include "client.h"

int	receive_server_output(int sock, int *connected)
{
  char	buff[300];
  int	red;

  if ((red = read(sock, buff, 300)) < 0)
    return (error_exit("ERROR: read server failed.\n"));
  buff[red] = '\0';
  write(1, buff, strlen(buff));
  if (!strncmp(buff, "230", 3))
    *connected = 1;
  if (!strncmp(buff, "221", 3))
    return (-1);
  return (0);
}

int	prompt(int *commands_num, char *buff, int sock)
{
  int	red;

  my_putnbr(*commands_num);
  *commands_num += 1;
  write(1, ")->", 3);
  if (!(red = read(0, buff, 1024)))
    {
      write(1, "\nService closing control connection.\n", 37);
      write(1, "Logged out if appropriate.\n\n", 28);
      close(sock);
      return (0);
    }
  buff[red] = '\0';
  return (0);
}

int	interact(char *buff, int sock, int *connected)
{
  char	*instr;
  char	*arg;

  if (!(instr = get_instructions(buff)))
    return (error_exit("ERROR: allocation failed.\n"));
  if (buff_has_arg(buff))
    {
      if (!(arg = get_arg(buff)))
	return (error_exit("ERROR: allocation failed.\n"));
    }
  else 
    arg = NULL;
  if (translate_one(sock, instr, arg, connected) == -1)
    return (-1);
  if (!strcmp(instr, "get") && arg && *connected)
    receive_file(sock, arg);
  else if (!strcmp(instr, "put") && arg && *connected)
    send_file(sock, arg);
  else if (!strcmp(instr, "ls") && *connected)
    receive_ls(sock);
  else if (strlen(instr))
    if (receive_server_output(sock, connected) == -1)
      return (-1);
  return (0);
}

int	communicate(int sock)
{
  char	buff[200];
  int	commands_num;
  int	connected;

  commands_num = 1;
  connected = 0;
  while (1)
    {
      prompt(&commands_num, buff, sock);
      if (interact(buff, sock, &connected) == -1)
	{
	  close(sock);
	  return (-1);
	}
      memset(buff, 0, strlen(buff));
    }
  close(sock);
  return (0);
}

int			main(int argc, char **argv)
{
  int			sock;
  socklen_t		server_len;
  struct sockaddr_in	server;
  char			buff[35];
  int			red;

  if (argc != 3)
    return (error_exit("USAGE: ./client ip_addr port\n"));
  if ((sock = setsock(&server, &server_len, argv)) == -1)
    return (error_exit("ERROR: socket failed.\n"));
  if (connect(sock, (struct sockaddr *)&server, server_len) == - 1)
    {
      close(sock);
      return (error_exit("ERROR: connect failed.\n"));
    }
  red = read(sock, buff, 33);
  buff[red] = '\n';
  buff[red++] = 0;
  write(1, buff, strlen(buff));
  if (communicate(sock) == -1)
    {
      close(sock);
      return (-1);
    }
  return (0);
}
