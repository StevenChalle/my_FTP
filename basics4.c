/*
** basics4.c for myftp in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Tue Mar 17 15:13:04 2015 Steven Challe
** Last update Fri Jul 10 14:03:30 2015 Steven Challe
*/

#include "server.h"
#include "client.h"

int	send_error(int client_sock, char *error)
{
  write(client_sock, error, strlen(error));
  return (-1);
}

int	send_error_in_treatmt(int client_sock, char *error, int *treated)
{
  *treated = 1;
  write(client_sock, error, strlen(error));
  return (-1);
}

int	fill_client_info(t_cinfo *client_info, int sock, char **env)
{
  client_info->sock = sock;
  client_info->co = 0;
  if (!(client_info->username = strdup("Anonymous")))
    return (error_exit("ERROR: allocation failed.\n"));
  client_info->password = NULL;
  if (!(client_info->base_dir = fill_pwd(env)))
    return (error_exit("ERROR: allocation failed.\n"));
  if (!(client_info->pwd = fill_pwd(env)))
    return (error_exit("ERROR: allocation failed.\n"));
  return (0);
}

int	check_if_cmd_treated(int treated, int client_sock, char *instr, char *error)
{
  if (!treated)
    {
      if (!(error = my_strconc("906 '", instr)))
        return (send_error(client_sock, "ERROR: allocation failed.\n"));
      if (!(error = my_strconc(error, "' command not found.\n")))
        return (send_error(client_sock, "ERROR: allocation failed.\n"));
      write(client_sock, error, strlen(error));
      free(error);
    }
  return (0);
}
