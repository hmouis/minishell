NAME=minishell

SRC= main.c\
parsing/pars_utils1.c \
parsing/pars_utils2.c \
parsing/syntax_error.c \
getenv/get_env.c \
tokenization/type_of_tokens.c \
tokenization/user_input1.c \
tokenization/user_input.c \
tokenization/utils.c \
tokenization/utils1.c \
expansion/expansion_again.c \
expansion/utils1.c \
expansion/utils2.c \
expansion/utils3.c \
expansion/utils4.c \
expansion/utils5.c \
expansion/utils6.c \
expansion/utils7.c \
execution/add_args_to_array.c \
execution/get_path.c \
execution/exec.c \
execution/exec_pipe.c \
execution/apply_redirect.c \
execution/pars_redirect.c \
execution/update_env.c \
execution/pipe_helpers.c \
execution/pipe_setup.c \
builtins/env.c \
getenv/env_utils.c \
builtins/echo.c \
builtins/pwd.c \
builtins/export.c \
builtins/unset.c \
builtins/cd.c \
builtins/export_utils.c \
builtins/exit.c \
builtins/is_builtins.c \
builtins/add_or_update_env.c \
expansion/expansion_again.c \
gc/garbage_collector.c \
gc/gc_utils.c \
utils/utils__1.c \
utils/utils__2.c \
parsing/herdoc.c \
parsing/herdoc_utils1.c

CC= cc 
CFLAGS= -Wall -Wextra -Werror
RFLAG= -lreadline
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJS= $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(RFLAG) $(LIBFT)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)


re: fclean all

