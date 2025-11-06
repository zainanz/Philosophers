# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zali <zali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 15:45:26 by zali              #+#    #+#              #
#    Updated: 2025/11/06 15:45:28 by zali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
C_FLAG = -Wall -Werror -Wextra
SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}
NAME = philo
limit = 200

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${C_FLAG} ${OBJ} -o ${NAME}
%.o: %.c 
	${CC} ${C_FLAG} -c -I. $< -o $@ -D MAX_LIMIT=${limit}
clean:
	rm -rf ${OBJ}
fclean: clean
	rm -rf ${NAME}
re: fclean ${NAME}
.PHONY: max
