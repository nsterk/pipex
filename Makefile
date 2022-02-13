# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:53:28 by nsterk        #+#    #+#                  #
#    Updated: 2022/02/10 15:18:41 by naomisterk    ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror

SHARED_SRCS	=	srcs/utils.c srcs/ft_split.c 
MAIN_SRCS	=	srcs/main.c srcs/get_commands.c srcs/children.c \
				srcs/pipes.c srcs/exit.c
BONUS_SRCS	=	srcs/main_bonus.c srcs/get_commands_bonus.c \
				srcs/pipes_bonus.c srcs/children_bonus.c \
				srcs/exit_bonus.c

ifdef bonus
SRCS		=	$(SHARED_SRCS) $(BONUS_SRCS)
else
SRCS		=	$(SHARED_SRCS) $(MAIN_SRCS)
endif

OBJS	=	$(SRCS:%.c=%.o)

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