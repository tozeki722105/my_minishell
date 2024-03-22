# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:18:29 by tofujiwa          #+#    #+#              #
#    Updated: 2024/03/08 03:21:42 by tozeki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror 
# RL_FLAGS	=	-lreadline -L $(brew --prefix readline)/lib -I $(brew --prefix readline)/include
RL_FLAGS	=	-lreadline
SRCS		=	_bool_utils.c \
				_env_utils.c \
				_free_utils.c \
				_libftwrap_utils.c \
				_print_utils.c \
				_syswrap_utils.c \
				_tkn_utils.c \
				_utils.c \
				init.c \
				tokenize.c \
				parse.c \
				expansion.c\
				execute.c \
				run_heredoc.c \
				main.c
OBJS		=	$(SRCS:.c=.o)
LIBFTPATH	=	libft/

all : $(NAME)

$(NAME): $(OBJS)
	make all -C $(LIBFTPATH)
	$(CC) $(CFLAGS) $(RL_FLAGS) $(OBJS) $(LIBFTPATH)libft.a -o $(NAME)

clean :
	make clean -C $(LIBFTPATH)
	rm -f $(OBJS)

fclean : clean
	make fclean -C $(LIBFTPATH)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
