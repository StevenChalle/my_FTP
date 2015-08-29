/*
** client.h for yo in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Mon Mar  9 14:52:39 2015 Steven Challe
** Last update Fri Jul 10 14:10:51 2015 Steven Challe
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>

//# include "basics.h"

/*
**client_funcs
*/
int	receive_file(int, char *);
int	send_file(int, char *);
int	receive_ls(int);

/*
**translate
*/
int	translate_one(int sock, char *instr, char *arg, int *connected);
int	translate_two(int sock, char *instr, char *arg, int *connected);
int	translate_three(int sock, char *instr, char *arg, int *connected);
int	translate_four(int sock, char *instr, char *arg, int *connected);


/*
** itoa_like
*/
char	*equal_zero(int num, char *str);
void	is_num_negative(int *num, int base, int *isnegative);
char	*reverse(char *str);
char	*itoa_like(int num, char *str, int base);

/*
**basics
*/
int	error_exit(char *);
int	file_len(char *);
int	receive_msg(int, char *, struct sockaddr_in);
char	**fill_commands(char **);
char	*get_arg(char *);
char	*get_instructions(char *);
void	my_putnbr(int);
void	aff_char_tab(char **);
char	*get_pwd_display(char *, char *);
int	buff_has_arg(char *);
char	*from_root_toserver(char *);
char	*get_xletters(char *, int, int);
int	prompt(int *commands_num, char *buff, int sock);
int	send_msg(int ssock, char *instr, char *arg, int *);
int	my_char_to_int(char c);
int	my_char_int(char c);
int	my_getnbr(const char *str);
int	get_int_length(int nb);
char	*twenty_digits(char number[20]);
char	*my_strconc(char *, char *);
int	setsock(struct sockaddr_in *server, socklen_t *server_len, char **argv);
char	*clean_command(char *);

#endif /* !CLIENT_H_ */
