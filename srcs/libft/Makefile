#COLOR

RED			:= '\033[0;31m'
GREEN		:= '\033[0;32m'
YELLOW		:= '\033[0;33m'
CYAN		:= '\033[0;36m'
PURPLE		:= '\033[0;35m'
OFF			:= '\033[0m'

#VARIABLE

SRCS		:= malloc/ft_calloc.c malloc/ft_split.c malloc/ft_strjoin.c mem/ft_bzero.c string/ft_strlcat.c string/ft_strlen.c string/ft_strncmp.c \
			string/ft_strcmp.c print/ft_putchar_fd.c print/ft_putendl_fd.c print/ft_putnbr_fd.c print/ft_putstr_fd.c print/ft_putstrnbr_fd.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS_DIR	:= ../../objs/libft/

OBJS		:= $(SRCS:.c=.o)

OBJS		:= $(addprefix $(OBJS_DIR),$(OBJS))

DEPS		:= $(OBJS:.o=.d)

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror -MMD -g3

NAME		:= libft.a

AR			:= ar rcs

RM			:= rm -f

#RULES

all		: ${NAME}

${NAME}	: ${OBJS}
		@${AR} ${NAME} ${OBJS}
		@echo ${NAME} ${GREEN}"done"${OFF}

clean	:
		@${RM} ${OBJS}
		@echo "All objects "${RED}"delete"${OFF}

fclean	: clean
		@${RM} ${NAME}
		@echo ${NAME} ${RED}"delete"${OFF}

re		: fclean all

.PHONY	: all clean fclean re

#RECETTE

-include $(DEPS)

$(OBJS_DIR)%.o	: %.c
			@mkdir -p $(@D)
	        @${CC} ${CFLAGS} -c $< -o $@
			@echo "Object\t$< "${GREEN}"done"${OFF}
