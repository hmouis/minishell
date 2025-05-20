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

SRC= expansion/expansion_utils.c parsing/pars_utils.c parsing/syntax_error.c  parsing/env.c parsing/pars_utils.c \
     tokenization/type_of_tokens.c tokenization/user_input1.c tokenization/user_input.c \
     tokenization/utils.c parsing/env.c  libft/ft_strcat.c libft/ft_strtok.c execution/exec.c

CC= cc
CFLAGS= -g3 
#-fsanitize=address
RFLAG= -lreadline

OBJS= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(RFLAG) $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
