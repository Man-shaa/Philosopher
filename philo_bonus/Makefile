NAME		=	philo_bonus

CORE_DIR	=	core/

CREATE_DIR	=	create/

PRINT_DIR	=	print/

PARSING_DIR	=	parsing/

UTILS_DIR	=	utils/

SRCS		=	main.c \
				${CORE_DIR}action.c \
				${CORE_DIR}checker.c \
				${CORE_DIR}routine.c \
				${CORE_DIR}time.c \
				${CREATE_DIR}create_data.c \
				${CREATE_DIR}create_semaphores.c \
				${CREATE_DIR}create_childs.c \
				${PARSING_DIR}parsing.c \
				${PRINT_DIR}print.c \
				${UTILS_DIR}utils.c

OBJS		=	${SRCS:.c=.o}

CC			=	clang

CFLAGS		=	-Wall -Werror -Wextra -g3 -pthread

RM			=	rm -rf

GREEN		=	\033[1;32m

DEFAULT		=	\033[0m

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:		
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}
		@echo "\n${GREEN}Everything cleaned${DEFAULT}"

re:			fclean
		$(MAKE) all -j

.PHONY:		all clean fclean re