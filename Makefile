# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afontain <afontain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 14:05:28 by besalort          #+#    #+#              #
#    Updated: 2023/11/27 17:42:32 by afontain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./src/main.c \
	./src/built_in/echo.c \
	./src/built_in/pwd.c \
	./src/built_in/exit.c \
	./src/built_in/env.c \
	./src/built_in/unset.c \
	./src/prompt.c \
	./src/ft_path.c \
	./src/is_cmd.c \
	./src/is_cmd2.c \
	./src/signal/signals.c \
	./src/signal/signals2.c \
	./src/free.c \
	
LIBFT_PATH = ./src/libft/

PIPEX_PATH = ./src/pipex/

LIBFT = $(LIBFT_PATH)libft.a

PIPEX = $(PIPEX_PATH)pipex.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

AR =  ar rcs

.c.o:	
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJ = $(SRC:.c=.o)

$(NAME)	:	${OBJ}
		make -C $(LIBFT_PATH)
		# make -C $(PIPEX_PATH)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

all	:	$(NAME)

clean :
		rm -rf $(OBJ)
		make clean -C $(LIBFT_PATH)
		make clean -C $(PIPEX_PATH)

fclean :	clean
		rm -rf $(NAME)
		make fclean -C $(LIBFT_PATH)
		make fclean -C $(PIPEX_PATH)

re : fclean all

.PHONY : all clean fclean re