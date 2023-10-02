# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 15:43:54 by blvilarn          #+#    #+#              #
#    Updated: 2023/09/22 17:09:49 by blvilarn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#VARIABLES
NAME = libft.a
HEADER = libft.h
FLAGS = -Wall -Werror -Wextra
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
	  ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
	  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	  ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_endswith.c get_next_line.c get_next_line_utils.c ft_printf.c str_utils.c int_utils.c \
	  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	  ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strjoin_free.c ft_atod.c ft_iswhitespace.c ft_isnum.c \
	  ft_memcontains.c ft_atol.c

OBJS = $(SRC:.c=.o)

#RULES

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#PHONY
.PHONY: all clean fclean re bonus
