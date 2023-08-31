# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besalort <besalort@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 14:57:22 by besalort          #+#    #+#              #
#    Updated: 2023/08/31 16:34:33 by besalort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_atoi.c \
		ft_atoi_long.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcpy.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		./printf/ft_printf.c \
		./printf/ft_adress.c \
		./printf/ft_convertbase.c \
		./printf/ft_putchar_i.c \
		./printf/ft_putstr_i.c \
		./printf/ft_putnbr_i.c \
		./printf/ft_putnbr_u.c \

SRCS_B =	ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstmap.c \



OBJS = ${SRCS:.c=.o}

OBJS_B = ${SRCS_B:.c=.o}

OBJS_TOTAL = ${OBJS} ${OBJS_B}

CC = gcc

RM	= rm -f

CFLAGS = -Wall -Werror -Wextra

AR = ar rcs

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS_TOTAL}
	${AR} $(NAME) ${OBJS_TOTAL}
	
all:	$(NAME)

clean:
	${RM} ${OBJS} ${OBJS_B}

fclean:	clean
	${RM} $(NAME)

re:	fclean all

bonus:	${OBJS} ${OBJS_B}
	${AR} $(NAME) ${OBJS} ${OBJS_B}

.PHONY:	all clean fclean re
