NAME = libft.a

SRC = \
  ft_is_alnum.c \
  ft_atoi.c \
  ft_is_alpha.c \
  ft_is_digits.c \
  ft_putstr_fd.c \
  ft_strcat.c \
  ft_strchr.c \
  ft_strcmp.c \
  ft_itoa.c \
  ft_strdup.c \
  ft_strncpy.c \
  ft_strtok.c \
  ft_substr.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
