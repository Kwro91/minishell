# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besalort <besalort@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 14:19:30 by besalort          #+#    #+#              #
#    Updated: 2023/08/31 16:35:53 by besalort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRC = ./pipex.c \
	./ft_free.c \
	./ft_open.c \
	./ft_path.c \
	./ft_load.c \
	./ft_access.c \
	./ft_processes.c \
	./ft_cmd.c \
	./ft_list.c \
	./ft_run.c \
	./ft_here_doc.c \

LIBFT = $(LIBFT_PATH)libft.a

LIBFT_PATH = ../libft/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	${AR} $(NAME) ${OBJ}


all : $(NAME)

clean :
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY : all clean fclean re
