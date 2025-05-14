NAME=a

SRC= gc.c main.c expansion/expansion_utils.c parsing/pars_utils.c parsing/syntax_error.c tokenization/type_of_tokens.c tokenization/user_input1.c tokenization/user_input.c tokenization/utils1.c tokenization/utils.c parsing/env.c

CC= cc
CFLAGS= -g 
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
