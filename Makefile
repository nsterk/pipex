# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:53:28 by nsterk        #+#    #+#                  #
#    Updated: 2022/03/08 09:47:15 by naomisterk    ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror

SRCS		=	srcs/main.c srcs/get_commands.c srcs/pipes.c srcs/children.c \
				srcs/process_management.c srcs/utils/utils.c srcs/utils/exit.c \
				srcs/utils/ft_split.c srcs/utils/free_functions.c 

OBJS		=	$(SRCS:%.c=%.o)

ifdef debug
FLAGS	+= -g
endif

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(FLAGS) -Iinc -o pipex
	make clean

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus