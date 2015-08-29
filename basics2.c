/*
** client.c for sockets in /home/challe_s/rendu/PSU_2015_myftp/tp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Wed Mar  4 10:58:39 2015 Steven Challe
** Last update Wed Jul  8 11:59:49 2015 Steven Challe
*/

#include "server.h"

void	my_putnbr(int nb)
{
  char	c;

  if (nb < 0)
    {
      write(1, "-", 1);
      nb *= -1;
    }
  if (nb >= 10)
    {
      my_putnbr(nb / 10);
      my_putnbr(nb % 10);
    }
  else
    {
      c = nb + 48;
      write(1, &c, 1);
    }
}

char	*my_strconc(char *s1, char *s2)
{
  char	*dest;
  int	k;
  int	w;

  if (!(dest = malloc(sizeof(char) * (strlen(s1) + strlen(s2)))))
    return (NULL);
  k = 0;
  w = 0;
  while (s1[w])
    {
      dest[k] = s1[w];
      k++;
      w++;
    }
  w = 0;
  while (s2[w])
    {
      dest[k] = s2[w];
      k++;
      w++;
    }
  dest[k] = '\0';
  return (dest);
}

void	aff_char_tab(char **tab)
{
  int	k;

  k = 0;
  while (tab[k] != NULL)
    {
      write(1, tab[k], strlen(tab[k]));
      write(1, "\n", 1);
      k++;
    }
}

char	*get_instructions(char *buff)
{
  char	*instr;
  int	k;
  int	w;

  if (!(instr = malloc(sizeof(char) * 5)))
    {
      error_exit("ERROR: malloc failed.\n");
      return (NULL);
    }
  k = 0;
  while (buff[k] == ' ' && buff[k] == '\t')
    k++;
  if (strlen(buff) == (size_t)k)
    {
      free(instr);
      return (NULL);
    }
  w = 0;
  while (buff[k] && buff[k] != '\n' && buff[k] != '\r' && buff[k] != ' ')
    instr[w++] = buff[k++];
  instr[w] = '\0';
  return (instr);
}

char	*fill_pwd(char **env)
{
  char	*pwd;
  int	k;
  int	w;
  int	o;

  if (!(pwd = malloc(sizeof(char) * 255)))
    return (NULL);
  k = 4;
  o = 0;
  w = 0;
  while (env[w])
    {
      if (env[w][0] == 'P' && env[w][1] == 'W' && env[w][2] == 'D')
	{
	  while (env[w][k])
	    {
	      pwd[o] = env[w][k];
	      o++;
	      k++;
	    }
	  pwd[o] = '\0';
	}
      w++;
    }
  return (pwd);
}
