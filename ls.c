/*
** ls.c for ftp in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Wed Jul  8 14:32:01 2015 Steven Challe
** Last update Wed Jul  8 15:32:31 2015 Steven Challe
*/

#include "server.h"

DIR	*open_dir(DIR *current_dir, int sock, int *done)
{
  *done = 0;
  if (!(current_dir = opendir(".")))
    {
      send_error(sock, "900 Failed opening current directory.               \r\n");
      return (NULL);
    }
  write(sock, "150 File status okay; about to open data connection.\r\n", 54);
  return (current_dir);
}

char	*add_file_in_msg(int *done, char *msg, struct dirent *tmp)
{
  if (!*done)
    {
      if (!(msg = my_strconc(tmp->d_name, "\n")))
	return (NULL);
    }
  else
    {
      if (!(msg = my_strconc(msg, tmp->d_name)))
	return (NULL);
      if (!(msg = my_strconc(msg, "\n")))
	return (NULL);
    }
  *done = 1;
  return (msg);
}

char		*store_output(char *msg, int sock, int *done)
{
  DIR		*current_dir;
  struct dirent	*tmp;

  current_dir = NULL;
  if (!(current_dir = open_dir(current_dir, sock, done)))
    return (NULL);
  while ((tmp = readdir(current_dir)))
    {
      if (tmp->d_name[0] != '.')
	{
	  if (!(msg = add_file_in_msg(done, msg, tmp)))
	    return (NULL);
	}
    }
  closedir(current_dir);
  return (msg);
}
