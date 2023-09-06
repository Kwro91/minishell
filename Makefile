# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besalort <besalort@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 14:05:28 by besalort          #+#    #+#              #
#    Updated: 2023/09/06 17:29:49 by besalort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./src/main.c \
	./src/is_cmd.c \
	./src/free.c \
	./src/ft_path.c \
	./src/prompt.c \
	./src/echo.c \
	./src/pwd.c \
	./src/signals.c \
	./src/exit.c \
	
LIBFT_PATH = ./src/libft/

PIPEX_PATH = ./src/pipex/

LIBFT = $(LIBFT_PATH)libft.a

PIPEX = $(PIPEX_PATH)pipex.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

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