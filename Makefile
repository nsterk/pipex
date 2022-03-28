# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 14:53:28 by nsterk        #+#    #+#                  #
#    Updated: 2022/03/28 14:16:13 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -g
SRCS_SHARED	=	srcs/get_commands.c srcs/pipes.c srcs/children.c \
			srcs/process_management.c srcs/utils/utils_01.c srcs/utils/exit.c \
			srcs/utils/ft_split.c srcs/utils/utils_02.c 
SRCS_BONUS	=	srcs/main.c \
				srcs/utils/get_next_line.c srcs/utils/get_next_line_utils.c
SRCS_MANDATORY = srcs/main_mandatory.c

SRCS = $(SRCS_SHARED) $(SRCS_MANDATORY)

ifdef BONUS
SRCS = $(SRCS_SHARED) $(SRCS_BONUS)
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

bonus:
	@ $(MAKE) BONUS=1 all
	make clean

re: fclean all

.PHONY: all clean fclean re