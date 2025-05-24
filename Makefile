# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 18:29:04 by oait-h-m          #+#    #+#              #
#    Updated: 2025/05/19 18:39:42 by oait-h-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
SRC= main.c\
parsing/pars_utils.c \
parsing/syntax_error.c \
parsing/get_env.c \
tokenization/type_of_tokens.c \
tokenization/user_input1.c \
tokenization/user_input.c \
tokenization/utils.c \
tokenization/utils1.c \
expansion/expansion_again.c \
execution/add_args_to_array.c \
execution/exec.c \
builtins/env.c \
builtins/export.c \
builtins/is_builtins.c \
libft/ft_is_alnum.c \
libft/ft_is_alpha.c \
libft/ft_is_digits.c \
libft/ft_putstr_fd.c \
libft/ft_strcat.c \
libft/ft_strchr.c \
libft/ft_strcmp.c \
libft/ft_strdup.c \
libft/ft_strncpy.c \
libft/ft_strtok.c \
libft/ft_substr.c \


CC= cc
CFLAGS= -g2 -fsanitize=address
RFLAG= -lreadline -lncurses

OBJS= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(RFLAG) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
