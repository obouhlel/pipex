#COLOR

RED			:= '\033[0;31m'
GREEN		:= '\033[0;32m'
YELLOW		:= '\033[0;33m'
CYAN		:= '\033[0;36m'
PURPLE		:= '\033[0;35m'
OFF			:= '\033[0m'

#VARIABLES

NAME				:= pipex

#SRCS MANDATORY

SRCS_MANDATORY_DIR	:= srcs/pipex_mandatory/

SRCS_MANDATORY		:= main.c vars.c exec.c here_doc.c error.c

SRCS_MANDATORY		:= ${addprefix ${SRCS_MANDATORY_DIR},${SRCS_MANDATORY}}

#SRCS BONUS

SRCS_BONUS_DIR		:= srcs/pipex_bonus/

SRCS_BONUS			:= main.c vars.c exec.c here_doc.c error.c

SRCS_BONUS			:= ${addprefix ${SRCS_BONUS_DIR},${SRCS_BONUS}}

#OBJS

OBJS_DIR			:= ./objs/

OBJS				:= ${OBJS_MANDATORY} ${OBJS_BONUS}

#OBJS & DEPS MANDATORY

OBJS_MANDATORY		:= $(SRCS_MANDATORY:.c=.o)

DEPS_MANDATORY		:= ${OBJS_MANDATORY:.o=.d}

OBJS_MANDATORY		:= $(addprefix $(OBJS_DIR),$(OBJS_MANDATORY))

#OBJS & DEPS BONUS

OBJS_BONUS			:= $(SRCS_BONUS:.c=.o)

OBJS_BONUS			:= $(addprefix $(OBJS_DIR),$(OBJS_BONUS))

DEPS_BONUS			:= ${OBJS_BONUS:.o=.d}

#LIBS

DEPS				:= ${DEPS_MANDATORY} ${DEPS_BONUS}

LIB_DIR				:= libs/

LIBFT_DIR			:= srcs/libft/

LIBFT				:= libft.a

MAKE_LIBFT			:= ${addprefix ${LIBFT_DIR},${LIBFT}}

LIB_LIBFT			:= ${addprefix ${LIB_DIR},${LIBFT}}

PIPEX				:= pipex.a

LIB_PIPEX			:= ${addprefix ${LIB_DIR},${PIPEX}}

LIBS				:= ${LIB_PIPEX} ${LIB_LIBFT}

#COMMANDS

AR					:= ar rcs

CC					:= gcc

CFLAGS				:= -Wall -Wextra -Werror -MMD -g3

RM					:= rm -rf

MV					:= mv -f

MKDIR				:= mkdir -p

#RULES

all			: ${NAME}

${NAME}		: ${OBJS_MANDATORY}
			@${MKDIR} ${LIB_DIR}
			@make -C ${LIBFT_DIR}
			@${MV} ${MAKE_LIBFT} ${LIB_DIR}
			@${AR} ${LIB_PIPEX} ${OBJS_MANDATORY}
			@echo ${PIPEX} ${GREEN}"done"${OFF}
			@${CC} ${CFLAGS} ${LIBS} -o ${NAME}
			@echo ${NAME} ${GREEN}"done"${OFF}

bonus		: ${OBJS_BONUS}
			@${MKDIR} ${LIB_DIR}
			@make -C ${LIBFT_DIR}
			@${MV} ${MAKE_LIBFT} ${LIB_DIR}
			@${AR} ${LIB_PIPEX} ${OBJS_BONUS}
			@echo ${PIPEX} ${GREEN}"done"${OFF}
			@${CC} ${CFLAGS} ${LIBS} -o ${NAME}
			@echo ${NAME} ${GREEN}"done"${OFF}

clean		:
			@make clean -C ${LIBFT_DIR}
			@${RM} ${OBJS_DIR} ${LIB_DIR}
			@echo "All objects and library "${RED}"delete"${OFF}

fclean		: clean
			@${RM} ${NAME}
			@echo ${NAME} ${RED}"delete"${OFF}

re			: fclean all

.PHONY		: all clean fclean re test

#RECETTE

-include $(DEPS)

$(OBJS_DIR)%.o	: %.c
				@${MKDIR} $(@D)
	        	@${CC} ${CFLAGS} -c $< -o $@
				@echo "$@ "${GREEN}"done"${OFF}
