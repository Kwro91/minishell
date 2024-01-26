# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besalort <besalort@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 14:05:28 by besalort          #+#    #+#              #
#    Updated: 2024/01/26 15:40:55 by besalort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./src/main.c \
	$(BUILT_IN_PATH)utils.c \
	$(BUILT_IN_PATH)init_builtin.c \
	$(BUILT_IN_PATH)echo.c \
	$(BUILT_IN_PATH)pwd.c \
	$(BUILT_IN_PATH)exit.c \
	$(BUILT_IN_PATH)env.c \
	$(BUILT_IN_PATH)export.c \
	$(BUILT_IN_PATH)export_bis.c \
	$(BUILT_IN_PATH)unset.c \
	$(BUILT_IN_PATH)cd.c \
	./src/prompt.c \
	./src/ft_path.c \
	./src/is_cmd.c \
	./src/is_cmd2.c \
	./src/free.c \
	$(SIGNAL_PATH)signals.c \
	$(SIGNAL_PATH)signals2.c \
	$(PIPEX_PATH)pipex.c \
	$(PIPEX_PATH)ft_free.c \
	$(PIPEX_PATH)ft_open.c \
	$(PIPEX_PATH)ft_path.c \
	$(PIPEX_PATH)ft_load.c \
	$(PIPEX_PATH)ft_access.c \
	$(PIPEX_PATH)ft_processes.c \
	$(PIPEX_PATH)ft_cmd.c \
	$(PIPEX_PATH)ft_list.c \
	$(PIPEX_PATH)ft_run.c \
	$(PIPEX_PATH)ft_here_doc.c \
	$(EXECUTION_PATH)execution.c \
	$(REDIRECTION_PATH)redir.c \
	$(REDIRECTION_PATH)redir_utils.c \
	$(REDIRECTION_PATH)redir_in_out.c \
	$(REDIRECTION_PATH)redir_rewrite.c \
	$(PARSE_PATH)split_parse.c \
	$(PARSE_PATH)check_line.c \
	
BUILT_IN_PATH = ./src/built_in/

EXECUTION_PATH = ./src/execution/

PARSE_PATH = ./src/parse/

REDIRECTION_PATH = ./src/redirection/

SIGNAL_PATH = ./src/signal/

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