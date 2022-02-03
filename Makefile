# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:53:28 by nsterk        #+#    #+#                  #
#    Updated: 2022/02/03 00:49:33 by naomisterk    ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g

SRCS		=	srcs/main.c srcs/utils/ft_strjoin.c srcs/utils/ft_split.c \
				srcs/utils/ft_strcmp.c srcs/utils/ft_strncmp.c
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