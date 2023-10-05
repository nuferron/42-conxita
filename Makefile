# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 14:21:33 by nuferron          #+#    #+#              #
#    Updated: 2023/10/05 19:53:10 by blvilarn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED =	\033[1;31m
GREEN =	\033[1;32m
YELLOW = \033[1;33m
BLUE =	\033[1;34m
PURPLE = \033[1;35m
CYAN =	\033[1;36m
WHITE =	\033[1;37m
RESET =	\033[0m

SRCS_CONXITA = conxita.c conxita_handler.c
SRCS_PROMPT = prompt_handler.c raw_prompt.c comp_counter.c quote_handler.c
SRCS_UTILS = bool_utils.c
SRCS_SIGNALS = signal_handler.c
SRCS_REDIRECTIONS = chevrons.c

SRCS = $(addprefix conxita/,$(SRCS_CONXITA)) $(addprefix prompt/,$(SRCS_PROMPT)) \
	   $(addprefix utils/,$(SRCS_UTILS)) $(addprefix signals/,$(SRCS_SIGNALS)) \
	   $(addprefix redirections/,$(SRCS_NURIA))

SRCDIR = src/
OBJDIR = obj/
HEADER = conxita.h
LIB = libs/libft/
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address
OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))
NAME = conxita
COLUMNS = $(shell tput cols)

RLINE_DIR   := libs/readline/
RLINE		:= $(addprefix $(RLINE_DIR),libreadline.a)
RLINE_H		:= $(addprefix $(RLINE_DIR),libhistory.a)
RLINE_FL    := -lreadline -ltermcap -lhistory

all: make_libs ${NAME}

${NAME}: ${OBJS}
	# cc ${CFLAGS} -lreadline ${OBJS} ${LIB} -o $@
	@$(CC) -ltermcap $(RLINE_H) $(RLINE) -L $(LIB) -lft $(OBJS) -o $(NAME)
	printf "${WHITE}CONXITA: ${GREEN}Binary compiled!${RESET}\n"

make_libs:
	make -C libs/libft --no-print-directory

${OBJDIR}%.o: ${SRCDIR}%.c ${HEADER}
	@printf "${WHITE}CONXITA: ${CYAN}Compiling files: ${WHITE}$(notdir $<)...${RESET}\r"
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} -c $< -o $@
	@printf "\r%-${COLUMNS}s\r"

leaks: ${NAME}
	leaks -atExit -- ./${NAME} ${ARGS}

norm:
	make -C libft norm --no-print-directory
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

.SILENT: ${NAME} make_libs all clean fclean norm do_bonus
.PHONY: all make_libs
