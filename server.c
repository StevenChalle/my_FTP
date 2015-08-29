/*
** socket.c for sockettp in /home/challe_s/rendu/PSU_2015_myftp/tp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Mon Mar  2 16:38:48 2015 Steven Challe
** Last update Wed Jun 17 10:52:05 2015 Steven Challe
*/

#include "server.h"

int			bind_listen(int sock, char *port)
{
  struct sockaddr_in	server;
  socklen_t		server_len;

  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(port));
  server.sin_addr.s_addr = INADDR_ANY;
  server_len = sizeof(server);
  if (bind(sock, (struct sockaddr *)&server, server_len) == -1)
    {
      close(sock);
      strerror(errno);
      return (error_exit("ERROR: bind failed.\n"));
    }
  if (listen(sock, 10) == -1)
    {
      close(sock);
      return (error_exit("ERROR: listen failed.\n"));
    }
  return (0);
}

int			receive_input(int sock, char **env)
{
  int			client_sock;
  socklen_t		*client_len;
  struct sockaddr_in	client;

  if (!(client_len = malloc(sizeof(socklen_t))))
    return (error_exit("ERROR: malloc failed.\n"));
  *client_len = sizeof(client);
  while (1)
    {
      if ((client_sock = accept(sock, (struct sockaddr *)&client, client_len)) == -1)
	{
	  free(client_len);
	  close(client_sock);
	  return (error_exit("ERROR: accept failed.\n"));
	}
      if (handle_input(client, client_sock, env) == -1)
	{
	  free(client_len);
	  return (-1);
	}
    }
  return (0);
}

int	main(int argc, char **argv, char **env)
{
  int	sock;

  if (argc != 2)
    return (error_exit("USAGE: ./server port"));
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (error_exit("ERROR: socket failed.\n"));
  if (bind_listen(sock, argv[1]) == -1) 
    return (-1);
  if (receive_input(sock, env) == -1)
    {
      close(sock);
      return (-1);
    }
  return (0);
}
