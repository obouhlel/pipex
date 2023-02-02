#COLOR

RED			:= '\033[0;31m'
GREEN		:= '\033[0;32m'
YELLOW		:= '\033[0;33m'
CYAN		:= '\033[0;36m'
PURPLE		:= '\033[0;35m'
OFF			:= '\033[0m'

#VARIABLES

NAME				:= pipex

NAME_BONUS			:= pipex_bonus

#SRCS MANDATORY

SRCS_MANDATORY_DIR	:= srcs/pipex_mandatory/

SRCS_MANDATORY		:= main.c vars.c exec.c error.c

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

DEPS_BONUS			:= ${OBJS_BONUS:.o=.d}

OBJS_BONUS			:= $(addprefix $(OBJS_DIR),$(OBJS_BONUS))

DEPS				:= ${DEPS_MANDATORY} ${DEPS_BONUS}

#LIB

LIB_DIR				:= ./srcs/libft/

LIB					:= ./srcs/libft/libft.a

#COMMANDS

AR					:= ar rcs

CC					:= gcc

CFLAGS				:= -Wall -Wextra -Werror -MMD -g3

RM					:= rm -rf

MKDIR				:= mkdir -p

#RULES

all				: ${NAME}

bonus			: ${NAME_BONUS}

${NAME}			: ${LIB} ${OBJS_MANDATORY}
				@${CC} ${CFLAGS} ${OBJS_MANDATORY} -L ${LIB_DIR} -lft -o ${NAME}
				@echo ${NAME} ${GREEN}"done"${OFF}

${NAME_BONUS}	: ${LIB} ${OBJS_BONUS}
				@${CC} ${CFLAGS} ${OBJS_BONUS} -L ${LIB_DIR} -lft -o ${NAME_BONUS}
				@echo ${NAME_BONUS} ${GREEN}"done"${OFF}

${LIB}			:
				@make -C ${LIB_DIR}
				@echo ${LIB} ${GREEN}"done"${OFF}

clean			:
				@make clean -C ${LIB_DIR}
				@${RM} ${OBJS_DIR}
				@echo "All objects and library "${RED}"delete"${OFF}

fclean			: clean
				@make fclean -C ${LIB_DIR}
				@${RM} ${NAME} ${NAME_BONUS}
				@echo ${NAME} ${RED}"delete"${OFF}

re				: fclean all

.PHONY			: all clean fclean re test

#RECETTE

$(OBJS_DIR)%.o	: %.c
				@${MKDIR} $(@D)
	        	@${CC} ${CFLAGS} -c $< -o $@
				@echo "$@ "${GREEN}"done"${OFF}

-include $(DEPS)
