RED =	\033[1;31m
GREEN =	\033[1;32m
YELLOW = \033[1;33m
BLUE =	\033[1;34m
PURPLE = \033[1;35m
CYAN =	\033[1;36m
WHITE =	\033[1;37m
RESET =	\033[0m

SRCS_CONXITA = conxita.c conxita_handler.c conxita_input.c
SRCS_PROMPT = prompt_handler.c
SRCS_TOKENIZER = tokenizer.c token_counter.c token_populator.c quote_utils.c env_handler.c \
				replace_variable.c
SRCS_UTILS = bool_utils.c env_utils.c conversion_utils.c utils.c cmd_utils.c path_utils.c \
				len_utils.c red_utils.c builtin_utils.c free_stuff.c env_lst_utils.c \
				chev_utils.c
SRCS_SIGNALS = signal_handler.c signal_utils.c
SRCS_EXEC = execution.c heredoc.c redirections.c
SRCS_ERRORS = errors.c
SRCS_BUILTINS = echo.c pwd.c cd.c exit.c env.c export.c unset.c

SRCS = $(addprefix conxita/,$(SRCS_CONXITA)) $(addprefix prompt/,$(SRCS_PROMPT)) \
	   $(addprefix utils/,$(SRCS_UTILS)) $(addprefix signals/,$(SRCS_SIGNALS)) \
	   $(addprefix execution/,$(SRCS_EXEC)) $(addprefix tokenizer/,$(SRCS_TOKENIZER)) \
	   $(addprefix errors/,$(SRCS_ERRORS)) $(addprefix builtins/,$(SRCS_BUILTINS))

SRCDIR = src/
OBJDIR = obj/
HEADER = conxita.h
LIB = libs/libft/
CFLAGS = -Wall -Werror -Wextra -O3 -g -fsanitize=address
OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))
NAME = minishell
COLUMNS = $(shell tput cols)

RLINE_DIR   := libs/readline/
RLINE		:= $(addprefix $(RLINE_DIR),libreadline.a)
RLINE_H		:= $(addprefix $(RLINE_DIR),libhistory.a)
RLINE_FL    := -lreadline -ltermcap -lhistory

all: make_libs ${NAME}

${NAME}: ${OBJS}
	@$(CC) ${CFLAGS} -ltermcap $(RLINE_H) $(RLINE) -L $(LIB) -lft $(OBJS) -o $(NAME)
	printf "${WHITE}CONXITA: ${GREEN}Binary compiled!${RESET}\n"

make_libs:
	make -C libs/libft --no-print-directory

${OBJDIR}%.o: ${SRCDIR}%.c ${HEADER}
	@printf "${WHITE}CONXITA: ${CYAN}Compiling files: ${WHITE}$(notdir $<)...${RESET}\r"
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} -c $< -o $@
	@printf "\r%-${COLUMNS}s\r"

leaks: ${NAME}
	leaks -atExit -- ./${NAME}

exec: ${NAME}
	./${NAME}

norm:
	make -s -C ${LIB} norm
	printf "${WHITE}CONXITA\n${RESET}"
	norminette $(addprefix ${SRCDIR},$(SRCS)) ${HEADER} | grep -v "OK" \
	| awk '{if($$2 == "Error!") print "${RED}"$$1" "$$2; \
	else print "${RESET}"$$0}'

clean:
	if [ -d ${OBJDIR} ] ; then \
		rm -rf ${OBJDIR} ; \
		printf "${WHITE}CONXITA: ${RED}Objects have been deleted${RESET}\n"; \
	fi
	make -C libs/libft clean --no-print-directory

fclean: 	clean
	if [ -e ${NAME} ] ; then \
		rm -f ${NAME} ; \
		printf "${WHITE}CONXITA: ${RED}All existing binaries have been deleted${RESET}\n" ; \
	else printf "${WHITE}CONXITA: ${PURPLE}Already cleaned${RESET}\n" ; \
	fi
	make -C libs/libft fclean --no-print-directory

re:	fclean all

.SILENT: ${NAME} make_libs all clean fclean norm do_bonus exec
.PHONY: all make_libs
