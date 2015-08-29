/*
** translate.c for ftp in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Wed Jul  8 12:28:40 2015 Steven Challe
** Last update Wed Jul  8 17:18:43 2015 Steven Challe
*/

#include "client.h"

int	translate_one(int sock, char *instr, char *arg, int *connected)
{
  int	done;

  done = 0;
  if (!strcmp(instr, "user"))
    if (send_msg(sock, "USER", arg, &done) == - 1)
      return (error_exit("ERROR: allocation failed.\n"));
  if (!strcmp(instr, "pass") && *connected)
    if (send_msg(sock, "PASS", arg, &done) == - 1)
      return (error_exit("ERROR: allocation failed.\n"));
  if (!strcmp(instr, "cd") && *connected)
    if (send_msg(sock, "CWD", arg, &done) == - 1)
      return (error_exit("ERROR: allocation failed.\n"));
  if (!strcmp(instr, "dele") && *connected)
    if (send_msg(sock, "DELE", arg, &done) == - 1)
      return (error_exit("ERROR: allocation failed.\n"));
  if (!strcmp(instr, "cdup") && *connected)
    {
      write(sock, "CDUP\r\n", 6);
      done = 1;
    }
  if (!done)
    return (translate_two(sock, instr, arg, connected));
  return (0);
}

int	translate_two(int sock, char *instr, char *arg, int *connected)
{
  int	done;

  done = 0;
  if (!strcmp(instr, "help"))
    {
      write(sock, "HELP\r\n", 6);
      done = 1;
    }
  if (!strcmp(instr, "put") && *connected)
    done = 1;
  if (!strcmp(instr, "get") && *connected)
    {
      if (send_msg(sock, "RETR", arg, &done) == - 1)
	return (error_exit("ERROR: allocation failed.\n"));
    }
  if (!strcmp(instr, "pwd") && *connected)
    {
      write(sock, "PWD\r\n", 5);
      done = 1;
    }
  if (!done)
    return (translate_three(sock, instr, arg, connected));
  return (0);
}

int	translate_three(int sock, char *instr, char *arg, int *connected)
{
  int	done;

  done = 0;
  if (!strcmp(instr, "quit"))
    {
      write(sock, "QUIT\r\n", 6);
      done = 1;
    }
  if (!strcmp(instr, "noop"))
    {
      write(sock, "NOOP\r\n", 6);
      done = 1;
    }
  if (!done)
    return (translate_four(sock, instr, arg, connected));
  return (0);
}

int	translate_four(int sock, char *instr, char *arg, int *connected)
{
  int	done;

  done = 0;
  if (!strcmp(instr, "ls") && !arg && *connected)
    {
      write(sock, "LIST\r\n", 6);
      done = 1;
    }
  else if (!strcmp(instr, "ls") && arg && *connected)
    {
      if (send_msg(sock, "LIST", arg, &done) == - 1)
        return (error_exit("ERROR: allocation failed.\n"));
    }
  if (!done && strlen(instr))
    send_msg(sock, instr, arg, &done);
  return (0);
}
