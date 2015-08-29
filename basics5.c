/*
** basics5.c for yo in /home/challe_s/rendu/PSU_2014_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Tue Jun 16 17:17:24 2015 Steven Challe
** Last update Fri Jul  3 15:16:27 2015 Steven Challe
*/

#include "server.h"
#include "client.h"

int	send_msg(int ssock, char *instr, char *arg, int *done)
{
  char	*message;

  *done = 1;
  if (arg)
    {  
      if (!(message = my_strconc(instr, " ")))
	return (-1);
      if (!(message = my_strconc(message, arg)))
	return (-1);
      if (!(message = my_strconc(message, "\r\n")))
	return (-1);
      write(ssock, message, strlen(message));
    }
  else
    {
      if (!(message = my_strconc(instr, "\r\n")))
	return (-1);
      write(ssock, message, strlen(message));
    }
  return (0);
}

int	my_char_to_int(char c)
{
  int	i;
  char	ch;

  if ((c > 47) && (c < 58))
    {
      i = 0;
      ch = 48;
      while (i < 10)
        {
          if (ch == c)
            return (i);
          ch += 1;
          i += 1;
        }
      return (0);
    }
  return (0);
}

int	my_char_int(char c)
{
  if ((c > 47) && (c < 58))
    return (1);
  else
    return (0);
}

int	my_getnbr(const char *str)
{
  int	i;
  int	nb;
  int	j;

  i = 0;
  j = 0;
  nb = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '-' && j < 1)
        j += 1;
      else if (my_char_int(str[i]))
        {
          nb += my_char_to_int(str[i]);
          nb *= 10;
        }
      i += 1;
    }
  if (j == 1)
    return ((nb / 10) * (-1));
  else
    return (nb / 10);
  return (0);
}

int	get_int_length(int nb)
{
  int	k;

  k = 1;
  while (nb >= 10)
    {
      nb /= 10;
      k++;
    }
  return (k);
}
