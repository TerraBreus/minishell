CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilib/libft -lreadline -lncurses

SRC_DIR = src
LIBFT_DIR = lib/libft

SRCS = \
	$(SRC_DIR)/main.c \

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

NAME = a.out

ifneq ($(SHOW),1)
QUIET = @
endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(QUIET)make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(OBJS)
	$(QUIET)make -C $(LIBFT_DIR) clean

fclean: clean
	$(QUIET)rm -f $(NAME)
	$(QUIET)make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean re fclean