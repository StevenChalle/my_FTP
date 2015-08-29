/*
** server_funcs2.c for myftp in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Fri Mar 20 10:05:10 2015 Steven Challe
** Last update Thu Jul  9 11:56:49 2015 Steven Challe
*/

#include "server.h"

int	do_user(t_cinfo *client_info, char *arg, int *treated)
{
  *treated = 1;
  if (!arg)
    return (send_error(client_info->sock, "954 usage : user username.\r\n"));
  if (strcmp(arg, client_info->username))
    return (send_error(client_info->sock, "902 User is not known.\r\n"));
  client_info->co = 1;
  write(client_info->sock, "230 User logged in, proceed.\r\n", 30);
  return (0);
}

int	do_pass(t_cinfo *client_info, int *treated)
{
  *treated = 1;
  write(client_info->sock, "230 User logged in, proceed.\n", 29);
  return (0);
}

int	do_cd(char *destdir, t_cinfo *client_info, int *treated)
{
  char	*ch_dir;

  *treated = 1;
  if (!destdir)
    return (send_error(client_info->sock, "903 Current directory unchanged\r\n"));
  if (!(ch_dir = malloc(sizeof(char) * (strlen(client_info->pwd) + strlen(destdir) + 1))))
    return (send_error(client_info->sock, "903 Current directory unchanged\r\n"));
  if (destdir[0] != '/' && destdir[0] != '-' && destdir[0] != '.')
    {
      if (relativepath_cd(destdir, ch_dir, client_info) == -1)
	return (send_error(client_info->sock, "903 Current directory unchanged\r\n"));
    }
  else if (destdir[0] == '/')
    {
      if (standard_cd(destdir, ch_dir, client_info) == -1)
	return (send_error(client_info->sock, "903 Current directory unchanged\r\n"));
    }
  else if (destdir[0] == '.' && destdir[1] == '.')
    if (cd_to_father_d(ch_dir, client_info) == -1)
      return (send_error(client_info->sock, "903 Current directory unchanged\r\n"));
  return (0);
}

int	do_get(char *file_path, t_cinfo *client_info, int *treated)
{
  int	file_fd;
  char	*content;
  char	*number;
  int	red;

  *treated = 1;
  if ((file_fd = open(file_path, O_RDONLY)) == -1)
    return (send_error(client_info->sock, "904 Failed openning file.                           \r\n"));
  if (!(content = malloc(sizeof(char) * file_len(file_path))))
    return (-1);
  red = read(file_fd, content, file_len(file_path));
  content[red] = 0;
  write(client_info->sock, "150 File status okay; about to open data connection.\r\n", 54);
  if (!(number = malloc(sizeof(char) * 25)))
    return (-1);
  number = itoa_like(file_len(file_path), number, 10);
  if (!(number = twenty_digits(number)))
    return (-1);
  write(client_info->sock, number, 20);
  write(client_info->sock, content, strlen(content));
  close(file_fd);
  write(client_info->sock, "226 Closing data connection.\nRequested file action successful (for example, file transfert or file abort).\r\n", 108);
  return (0);
}

int	do_put(char *file_path, t_cinfo *client_info, int *treated)
{
  int	file_fd;
  char	*content;
  char	filelen[20];
  int	red;

  *treated = 1;
  if ((file_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    return (send_error(client_info->sock, "904 Failed openning new file, or filename exists.     \r\n"));
  write(client_info->sock, "150 File status okay; about to open data connection.\r\n", 54);
  red = read(client_info->sock, filelen, 20);
  filelen[red] = '\0';
  if (!(content = malloc(sizeof(char) * atol(filelen))))
    return (-1);
  red = read(client_info->sock, content, my_getnbr(filelen));
  content[red] = '\0';
  write(file_fd, content, strlen(content));
  close(file_fd);
  write(client_info->sock, "226 Closing data connection.\nRequested file action successful (for example, file transfert or file abort).\r\n", 108);
  return (0);
}
