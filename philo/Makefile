NAME    = philo

CC              = cc

CFLAGS  = -pthread -Wall -Wextra -Werror -g3 #-fsanitize=thread

RM              = rm -f

SRC     = parsing.c philo.c routine.c init.c utils.c monitor.c clear.c

OBJ	= ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	${RM} ${OBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
