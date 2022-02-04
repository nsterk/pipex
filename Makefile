# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:53:28 by nsterk        #+#    #+#                  #
#    Updated: 2022/02/04 20:31:19 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror

SRCS		=	srcs/main.c srcs/utils.c srcs/ft_split.c \
				srcs/get_commands.c srcs/children.c \
				srcs/pipes.c srcs/exit.c
OBJS		=	$(SRCS:%.c=%.o)

ifdef DEBUG
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