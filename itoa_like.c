/*
** itoa_like.c for yo in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Mon Jun 22 14:33:11 2015 Steven Challe
** Last update Wed Jul  8 15:26:34 2015 Steven Challe
*/

#include "server.h"

char	*reverse(char *str)
{
  char	*new;
  int	k;
  int	o;

  if (!(new = malloc(sizeof(char) * strlen(str))))
    return (NULL);
  k = strlen(str) - 1;
  o = 0;
  while (str[k] && k >= 0)
    new[o++] = str[k--];
  new[o] = '\0';
  return (new);
}

char	*equal_zero(int num, char *str)
{
  if (!num)
    {
      str[0] = '0';
      str[1] = '\0';
      return (str);
    }
  return (str);
}

void	is_num_negative(int *num, int base, int *isnegative)
{
  if (*num < 0 && base == 10)
    {
      *isnegative = 1;
      *num = *num * -1;
    }
}

char	*itoa_like(int num, char *str, int base)
{
  int	i;
  int	isnegative;
  int	rem;

  i = 0;
  isnegative = 0;
  str = equal_zero(num, str);
  if (!num)
    return (str);
  is_num_negative(&num, base, &isnegative);
  while (num)
    {
      rem = num % base;
      if (rem > 9)
	str[i++] = rem - 10 + 'a';
      else
	  str[i++] = rem + '0';
      num = num / base;
    }
  if (isnegative)
    str[i++] = '-';
  str[i] = '\0';
  if (!(str = reverse(str)))
    return (NULL);
  return (str);
}
