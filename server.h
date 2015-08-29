/*
** server.h for server in /home/challe_s/rendu/PSU_2015_myftp
** 
** Made by Steven Challe
** Login   <challe_s@epitech.net>
** 
** Started on  Thu Mar  5 12:05:14 2015 Steven Challe
** Last update Wed Jul  8 16:13:15 2015 Steven Challe
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <dirent.h>
# include <netdb.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include <unistd.h>

typedef struct	s_cinfo
{
  int		sock;
  int		co;
  char		*username;
  char		*password;
  char		*pwd;
  char		*base_dir;
}		t_cinfo;

/*
**server.c
*/
int	bind_listen(int sock, char *port);
int	receive_input(int sock, char **env);

/*
**handle_input.c
*/
int	handle_input(struct sockaddr_in, int, char **);
int	treat_command(char *, t_cinfo *);
int	receive_msg_and_treat(char *, int, struct sockaddr_in, t_cinfo *);
int	fork_it(int client_sock, int *pid);
int	close_client_exit(int client_sock);

/*
**ls.c
*/
DIR	*open_dir(DIR *, int, int *);
char    *add_file_in_msg(int *, char *, struct dirent *);
char	*store_output(char *msg, int, int *);

/*
**assign_behavior.c
*/
int	assign_behavior(char *, t_cinfo *, int *, char *);
int	assign_behavior2(char *, t_cinfo *, int *, char *);
int	assign_behavior3(char *, t_cinfo *, int *, char *);

/*
**server_funcs.c
*/
int	do_list(t_cinfo *, int *);
int	do_list_spe(t_cinfo *, char *, int *);
int	do_help(t_cinfo *, int *);
int	do_pwd(t_cinfo *, int *);
int	do_user(t_cinfo *, char *, int *);
int	do_pass(t_cinfo *, int *);
int	do_cd(char *, t_cinfo *, int *);
int	do_get(char *, t_cinfo *, int *);
int	do_put(char *, t_cinfo *, int *);
int	do_delete(t_cinfo *, char *, int *);

/*
** change_dir
*/
int	relativepath_cd(char *, char *, t_cinfo *);
int	standard_cd(char *, char *, t_cinfo *);
int	cd_to_father_d(char *, t_cinfo *);

/*
** itoa_like
*/
char	*equal_zero(int num, char *str);
void	is_num_negative(int *num, int base, int *isnegative);
char	*reverse(char *str);
char	*itoa_like(int num, char *str, int base);

/*
** basics
*/
int	error_exit(char *);
int	file_len(char *);
int	receive_msg(int, char *, struct sockaddr_in);
char	**fill_commands(char **);
char	*get_arg(char *);
char	*get_instructions(char *);
void	my_putnbr(int);
void	aff_char_tab(char **);
char	*fill_pwd(char **env);
char	*get_pwd_display(char *, char *);
char	*my_strconc(char *, char *);
int	buff_has_arg(char *);
char	*from_root_toserver(char *);
char	*get_xletters(char *, int, int);
char	*get_fatherpath(char *);
int	send_error(int, char*);
int	send_error_in_treatmt(int client_sock, char *error, int *treated);
int	fill_client_info(t_cinfo *, int, char **);
int	check_if_cmd_treated(int, int, char *, char *);
int	send_msg(int ssock, char *instr, char *arg, int *);
int	my_char_to_int(char c);
int	my_char_int(char c);
int     my_getnbr(const char *str);
int	get_int_length(int nb);
char	*twenty_digits(char number[20]);

#endif /* !SERVER_H_ */
