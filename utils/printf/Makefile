# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 20:46:37 by acarlott          #+#    #+#              #
#    Updated: 2022/12/09 10:05:17 by acarlott         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS = -Wall -Werror -Wextra
CC = gcc
AR = ar rcs
RM = rm -f
HEADER = printf.h

SRCS = ft_check_convert.c ft_printf.c ft_putchar.c ft_putnbr_int.c \
ft_putnbr_base.c ft_putnbr_unsigned.c ft_print_memory.c ft_putstr.c\

OBJS = ${SRCS:.c=.o}

%.o:	%.c Makefile
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o} -I ${HEADER}

all: ${NAME}
${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}

clean :
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re : clean all

.PHONY: all clean fclean re bonus
