/*
** receive_input.c for server in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Thu Mar  5 12:07:01 2015 Steven Challe
** Last update Fri Jul 10 14:06:04 2015 Steven Challe
*/

#include "server.h"

int	treat_command(char *buff, t_cinfo *client_info)
{
  char	*arg;
  char	*instr;
  int	treated;
  char	*error;

  arg = NULL;
  error = NULL;
  if (!(instr = get_instructions(buff)))
    return (send_error(client_info->sock, "ERROR: allocation failed.\n"));
  if (buff_has_arg(buff))
    {
      if (!(arg = get_arg(buff)))
	return (send_error(client_info->sock, "ERROR: allocation failed.\n"));
    }
  else
    arg = NULL;
  //  printf("buff = %s\n instr = %s\n arg = %s\n", buff, instr, arg);
  treated = 0;
  assign_behavior(instr, client_info, &treated, arg);
  if (check_if_cmd_treated(treated, client_info->sock, instr, error) == -1)
    return (-1);
  free(arg);
  free(instr);
  return (0);
}

int	receive_msg_and_treat(char *buff, int client_sock, struct sockaddr_in client, t_cinfo *client_info)
{
  while (strcmp(buff, "QUIT"))
    {
      if (receive_msg(client_sock, buff, client) == -1)
        {
          close(client_sock);
          return (0);
        }
      if (treat_command(buff, client_info) == -1)
        {
          close(client_sock);
          return (-1);
        }
    }
  return (0);
}

int	fork_it(int client_sock, int *pid)
{
  if ((*pid = fork()) == -1)
    {
      close(client_sock);
      return (error_exit("ERROR: fork failed.\n"));
    }
  return (0);
}

int	close_client_exit(int client_sock)
{
  close(client_sock);
  return (-1);
}

int		handle_input(struct sockaddr_in client, int client_sock, char **env)
{
  char		buff[1024];
  t_cinfo	client_info;
  int		pid;

  if ((fork_it(client_sock, &pid)) == -1)
      return (error_exit("ERROR: fork failed.\n"));
  if (!pid)
    {
      buff[0] = '\0';
      write(client_sock, "220 Service ready for new user.\r\n", 33);
      if (fill_client_info(&client_info, client_sock, env) == -1)
	return (close_client_exit(client_sock));
      if (receive_msg_and_treat(buff, client_sock, client, &client_info) == -1)
	return (close_client_exit(client_sock));
      close(client_sock);
      exit(0);
    }
  if (pid > 0)
    close(client_sock);
  return (0);
}
