/*
** basics3.c for myftp in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Tue Mar 10 00:13:49 2015 Steven Challe
** Last update Wed Jun 17 11:36:42 2015 Steven Challe
*/

#include "server.h"
#include "client.h"

char	*get_xletters(char *pwd, int k, int x)
{
  char	*xletters;
  int	w;

  if (!(xletters = malloc(sizeof(char) * x)))
    return (NULL);
  w = 0;
  while (pwd[k] && pwd[k] != '/' && w < x)
    {
      xletters[w] = pwd[k];
      w++;
      k++;
    }
  xletters[w] = '\0';
  return (xletters);
}

char	*get_pwd_display(char *pwd, char *display)
{
  char	*tmp;
  int	k;
  int	w;

  if (!(display = malloc(sizeof(char) * 255)))
    return (NULL);
  if (!(tmp = malloc(sizeof(char) * strlen("/server"))))
    return (NULL);
  k = 0;
  w = 0;
  while (pwd[k])
    {
      if (!(tmp = get_xletters(pwd, k, 7)))
	return (NULL);
      if (!strcmp(tmp, "/server"))
	{
	  while (pwd[k])
	    display[w++] = pwd[k++];
	  display[w] = '\0';
	}
      k++;
    }
  return (display);
}

int	buff_has_arg(char *buff)
{
  int	k;

  k = 0;
  while (buff[k] && buff[k] != ' ')
    k++;
  if ((unsigned)k == strlen(buff))
    return (0);
  while (buff[k] && (buff[k] == ' ' || buff[k] == '\n' || buff[k] == '\r'))
    k++;
  if ((unsigned)k == strlen(buff))
    return (0);
  return (1);
}

char	*from_root_toserver(char *pwd)
{
  char	*path_beginning;
  char	*tmp;
  int	k;

  if (!(path_beginning = malloc(sizeof(char) * strlen(pwd))))
    return (NULL);
  if (!(tmp = malloc(sizeof(char) * strlen("/server"))))
    return (NULL);
  k = 0;
  while (pwd[k])
    {
      if (!(tmp = get_xletters(pwd, k, 7)))
	return (NULL);
      if (!strcmp(tmp, "/server"))
	{
	  path_beginning[k] = '\0';
	  return (path_beginning);
	}
      path_beginning[k] = pwd[k];
      k++;
    }
  return (path_beginning);
}

char	*get_fatherpath(char *pwd)
{
  char	*father;
  int	k;
  int	j;

  if (!(father = malloc(sizeof(char) * strlen(pwd))))
    return (NULL);
  k = strlen(pwd);
  while (k >= 0 && pwd[k] != '/')
    k--;
  j = 0;
  while (k != 0)
    {
      father[j] = pwd[j];
      j++;
      k--;
    }
  father[j] = '\0';
  return (father);
}
