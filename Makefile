NAME=a

SRC= main.c\
parsing/pars_utils.c \
parsing/syntax_error.c \
tokenization/type_of_tokens.c \
tokenization/user_input1.c \
tokenization/user_input.c \
tokenization/utils1.c \
tokenization/utils.c \
parsing/env.c \
expansion/expansion_again.c \
gc/garbage_collector.c \
parsing/herdoc.c\
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
CFLAGS= -g3 -Wall -Wextra -Werror 
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
