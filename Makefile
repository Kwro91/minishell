# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besalort <besalort@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 14:05:28 by besalort          #+#    #+#              #
#    Updated: 2024/03/07 14:31:50 by besalort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./src/main.c \
	./src/prompt.c \
	./src/ft_path.c \
	./src/check_prompt.c \
	$(BUILT_IN_PATH)utils.c \
	$(BUILT_IN_PATH)init_builtin.c \
	$(BUILT_IN_PATH)echo.c \
	$(BUILT_IN_PATH)pwd.c \
	$(BUILT_IN_PATH)exit.c \
	$(BUILT_IN_PATH)env.c \
	$(BUILT_IN_PATH)export.c \
	$(BUILT_IN_PATH)export_bis.c \
	$(BUILT_IN_PATH)export_ter.c \
	$(BUILT_IN_PATH)unset.c \
	$(BUILT_IN_PATH)cd.c \
	$(EXECUTION_PATH)execution.c \
	$(EXECUTION_PATH)execution_utils.c \
	$(EXECUTION_PATH)is_cmd.c \
	$(EXECUTION_PATH)is_cmd2.c \
	$(FREE_PATH)end_loop.c \
	$(FREE_PATH)free.c \
	$(FREE_PATH)free_utils.c \
	$(SIGNAL_PATH)signals.c \
	$(SIGNAL_PATH)signals2.c \
	$(REDIRECTION_PATH)redir.c \
	$(REDIRECTION_PATH)redir_utils.c \
	$(REDIRECTION_PATH)redir_in_out.c \
	$(REDIRECTION_PATH)redir_rewrite.c \
	$(REDIRECTION_PATH)redir_close.c \
	$(REDIRECTION_PATH)here_doc.c \
	$(REDIRECTION_PATH)reset_redir.c \
	$(REDIRECTION_PATH)sub_files.c \
	$(CHECK_CREATE_PATH)create_cmd.c \
	$(CHECK_CREATE_PATH)check_line.c \
	$(PIPE_PATH)child.c \
	$(PIPE_PATH)mpipex.c \
	$(PIPE_PATH)parent.c \
	$(DOLLAR_PATH)?.c \
	$(DOLLAR_PATH)dollar.c \
	$(DOLLAR_PATH)dollarquote.c \
	$(DOLLAR_PATH)letter.c \
	$(DOLLAR_PATH)other.c \
	$(DOLLAR_PATH)letter_utils.c \
	$(PARSING_PATH)parsing.c \
	$(PARSING_PATH)remove_quote.c \
	$(PARSING_PATH)remove_quote_utils.c \
	$(SPLIT_PATH)split_cmd.c \
	$(SPLIT_PATH)split_utils.c \
	

SPLIT_PATH = ./src/split/

FREE_PATH = ./src/free/

PARSING_PATH = ./src/parsing/

DOLLAR_PATH = ./src/parsing/dollar/

BUILT_IN_PATH = ./src/built_in/

EXECUTION_PATH = ./src/execution/

CHECK_CREATE_PATH = ./src/check_create/

REDIRECTION_PATH = ./src/redirection/

SIGNAL_PATH = ./src/signal/

LIBFT_PATH = ./src/libft/

PIPE_PATH = ./src/new_pipex/

LIBFT = $(LIBFT_PATH)libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

AR =  ar rcs

.c.o:	
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJ = $(SRC:.c=.o)

$(NAME)	:	${OBJ}
		make -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

all	:	$(NAME)

clean :
		rm -rf $(OBJ)
		make clean -C $(LIBFT_PATH)

fclean :	clean
		rm -rf $(NAME)
		make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY : all clean fclean re