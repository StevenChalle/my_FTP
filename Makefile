##
## Makefile for ftp in /home/challe_s/rendu/PSU_2015_myftp
## 
## Made by Steven Challe
## Login   <challe_s@epitech.net>
## 
## Started on  Wed Mar  4 19:06:28 2015 Steven Challe
## Last update Sat Aug 29 09:52:52 2015 Steven Challe
##

NAME =		server

CNAME =		client

SRC =		server.c \
		handle_input.c \
		assign_behavior.c \
		ls.c \
		server_funcs.c \
		server_funcs2.c \
		change_directory.c \
		itoa_like.c \
		basics.c \
		basics2.c \
		basics3.c \
		basics4.c \
		basics5.c \
		basics6.c

CSRC =		client.c \
		translate.c \
		client_funcs.c \
		itoa_like.c \
		basics.c \
		basics2.c \
		basics3.c \
		basics4.c \
		basics5.c \
		basics6.c

OBJ =		$(SRC:.c=.o)

COBJ =		$(CSRC:.c=.o)

CFLAGS =	-Wall -Wextra 

all:	$(NAME)	$(CNAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

$(CNAME):	$(COBJ)
	gcc -o $(CNAME) $(COBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(COBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f $(CNAME)

re:	fclean all

.PHONY: all  clean fclean re
