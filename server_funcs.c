/*
** server_funcs.c for ftp in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Thu Mar  5 17:33:06 2015 Steven Challe
** Last update Wed Jul  8 16:23:17 2015 Steven Challe
*/

#include "server.h"

int		do_list(t_cinfo *client_info, int *treated)
{
  char		*msg;
  char		*msglen;
  int		done;

  done = 0;
  *treated = 1;
  msg = NULL;
  if (!(msg = store_output(msg, client_info->sock, &done)))
    return (-1);
  if (!(msglen = malloc(sizeof(char) * 25)))
    return (-1);
  msglen = itoa_like(strlen(msg), msglen, 10);
  if (!(msglen = twenty_digits(msglen)))
    return (-1);
  write(client_info->sock, msglen, 20);
  write(client_info->sock, msg, strlen(msg));
  write(client_info->sock, "226 Closing data connection.\nRequested file", 43);
  write(client_info->sock, "action successful (for example, file", 36);
  write(client_info->sock, "transfert or file abort).\r\n", 27);
  if (!done)
    write(client_info->sock, "\n", 1);
  return (0);
}

int		do_list_spe(t_cinfo *client_info, char *destdir, int *treated)
{
  DIR		*dir;
  struct dirent	*tmp;
  char		*dir_tmp;
  int		done;

  done = 0;
  *treated = 1;
  if (!(dir_tmp = my_strconc(client_info->pwd, "/")))
    return (-1);
  if (!(destdir = my_strconc(dir_tmp, destdir)))
    return (-1);
  if (!(dir = opendir(destdir)))
    return (send_error(client_info->sock, "900 Failed openning current directory.\r\n"));
  while ((tmp = readdir(dir)))
    {
      if (tmp->d_name[0] != '.')
	{
	  done = 1;
	  write(client_info->sock, tmp->d_name, strlen(tmp->d_name));
	  write(client_info->sock, "\n", 1);
	}
    }
  if (!done)
    write(client_info->sock, "\n", 1);
  closedir(dir);
  return (0);
}

int	do_help(t_cinfo *client_info, int *treated)
{
  *treated = 1;
  write(client_info->sock, "214 Help message.\nOn how to use the server ", 43);
  write(client_info->sock, "or the meaning of a particular non-standard ", 44);
  write(client_info->sock, "command.\nThis reply is useful only to the ", 42);
  write(client_info->sock, "human user.\r\n", 13);
  return (0);
}

int	do_pwd(t_cinfo *client_info, int *treated)
{
  char	*display;

  *treated = 1;
  if (!(display = my_strconc(client_info->pwd, "\n")))
    return (-1);
  write(client_info->sock, display, strlen(display));
  return (0);
}

int	do_delete(t_cinfo *client_info, char *arg, int *treated)
{
  *treated = 1;
  if (!arg)
    return (send_error(client_info->sock, "967 usage : dele file.\r\n"));
  if (remove(arg) == -1)
    return (send_error(client_info->sock, "901 Failed removing directory.\r\n"));
  write(client_info->sock, "250 Requested file action okay, completed.\r\n", 44);
  return (0);
}
