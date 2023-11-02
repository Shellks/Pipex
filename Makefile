# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 19:07:46 by acarlott          #+#    #+#              #
#    Updated: 2023/04/25 19:32:37 by acarlott         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

CFLAGS = -Wall -Wextra -Werror
CC = cc
HEADER = ./include

PRINTF_PATH = ./utils/printf/
PRINTF_FILE = libftprintf.a
PRINTF_LIB = $(addprefix ${PRINTF_PATH}, ${PRINTF_FILE})

SRCS =	mandatory/main.c \
		mandatory/pipex.c \
		mandatory/pipex_init.c \
		mandatory/pipex_utils.c \
		mandatory/child_process.c \
		
SRCS_BONUS = bonus/main_bonus.c \
		bonus/pipex_bonus.c \
		bonus/pipex_init_bonus.c \
		bonus/pipex_utils_bonus.c \
		bonus/child_process_bonus.c \
		bonus/bonus_utils/ft_memset.c \
		bonus/bonus_utils/get_next_line.c \

SRCS_UTILS = utils/ft_strlen.c \
		utils/ft_split.c \
		utils/ft_strncmp.c \
		utils/ft_strjoin.c \

OBJS_UTILS = ${SRCS_UTILS:.c=.o}
	
OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

%.o:	%.c Makefile ${PRINTF_LIB} 
	${CC} ${CFLAGS} -I${HEADER} -g -c $< -o $@

all : ${NAME}

bonus : $(NAME_BONUS)

$(NAME_BONUS) :	${OBJS_UTILS} ${OBJS_BONUS} ${PRINTF_LIB} ${HEADER}/pipex_bonus.h
		echo "\033[1;34m\nCreate: \033[1;33mpipex_bonus"
		${CC} ${CFLAGS} ${OBJS_UTILS} ${OBJS_BONUS} ${PRINTF_LIB} -o ${NAME_BONUS}
		echo "\033[1;32mSucces !\n"

${NAME} : ${OBJS_UTILS} ${OBJS} ${PRINTF_LIB} ${HEADER}/pipex.h
	echo "\033[1;34m\nCreate: \033[1;33mpipex"
	${CC} ${CFLAGS} ${OBJS_UTILS} ${OBJS} ${PRINTF_LIB} -o ${NAME}
	echo "\033[1;32mSucces !\n"

$(PRINTF_LIB) : force
	make -C $(PRINTF_PATH)

force :

clean :
	echo "\033[1;31m\nClean: \033[1;36mAll *.o"
	${RM} ${OBJS} ${OBJS_BONUS} ${OBJS_UTILS}
	make clean -C ${PRINTF_PATH}
	echo "\033[1;32mDelete !\n"

fclean: clean
	echo "\033[1;31mClean: \033[1;36mAll *.a && executable"
	${RM} ${NAME} ${NAME_BONUS}
	make fclean -C ${PRINTF_PATH}
	echo "\033[1;32mDelete !\n"

re : fclean all

.SILENT:

.PHONY: all clean bonus fclean re force
