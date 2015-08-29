/*
** change_directoy.c for 42sh in /home/challe_s/rendu/42sh/42shlast/42sh.1.1
** 
** Made by challe_s challe_s
** Login   <challe_s@epitech.net>
** 
** Started on  Mon Sep  1 12:40:19 2014 challe_s challe_s
** Last update Wed Jul  8 12:09:34 2015 Steven Challe
*/

#include "server.h"

int	relativepath_cd(char *destdir, char *ch_dir, t_cinfo *client_info)
{
  if (!(ch_dir = my_strconc(client_info->pwd, "/")))
    return (-1);
  if (!(ch_dir = my_strconc(ch_dir, destdir)))
    return (-1);
  if (!access(ch_dir, F_OK))
    {
      if (chdir(ch_dir) == -1)
	return (-1);
      if (!(client_info->pwd = my_strconc(ch_dir, "")))
	return (-1);
      write(client_info->sock, "250 Requested file action okay, completed.\r\n", 44);
    }
  else
    return (-1);
  return (0);
}

int	standard_cd(char *destdir, char *ch_dir, t_cinfo *client_info)
{
  if (!(ch_dir = my_strconc(client_info->base_dir, destdir)))
    return (-1);
  if (!access(ch_dir, F_OK))
    {
      if (chdir(ch_dir) == -1)
	return (-1);
      if (!(client_info->pwd = my_strconc(ch_dir, "")))
	return (-1);
      write(client_info->sock, "250 Requested file action okay, completed.\r\n", 44);
    }
  else
    return (-1);
  return (0);
}

int	cd_to_father_d(char *ch_dir, t_cinfo *client_info)
{
  if (!(ch_dir = get_fatherpath(client_info->pwd)))
    return (-1);
  if (strncmp(ch_dir, client_info->base_dir, strlen(client_info->base_dir) - 1))
    {
      write(client_info->sock, "200 Command okay.\r\n", 19);
      return (0);
    }
  if (!access(ch_dir, F_OK))
    {
      if (chdir(ch_dir) == -1)
	return (-1);
      if (!(client_info->pwd = my_strconc(ch_dir, "")))
	return (-1);
      write(client_info->sock, "200 Command okay.\r\n", 19);
    }
  else
    return (-1);
  return (0);
}
