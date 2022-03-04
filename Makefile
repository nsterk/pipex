# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:53:28 by nsterk        #+#    #+#                  #
#    Updated: 2022/03/03 13:20:18 by naomisterk    ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifdef bonus
NAME		=	pipex_bonus
else
NAME		=	pipex
endif

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror

SHARED_SRCS	=	srcs/utils.c srcs/ft_split.c srcs/free_functions.c
MAIN_SRCS	=	srcs/main.c srcs/get_commands.c srcs/children.c \
				srcs/pipes.c srcs/exit.c
BONUS_SRCS	=	srcs/main_bonus.c srcs/get_commands_bonus.c \
				srcs/pipes_bonus.c srcs/children_bonus.c \
				srcs/exit_bonus.c srcs/process_management.c

ifdef bonus
SRCS		=	$(SHARED_SRCS) $(BONUS_SRCS)
else
SRCS		=	$(SHARED_SRCS) $(MAIN_SRCS)
endif

OBJS	=	$(SRCS:%.c=%.o)

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