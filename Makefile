CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilib/libft

MINILIB_FLAGS = -lreadline -lncurses

SRC_DIR = src
PARSE_DIR = parse
LIBFT_DIR = lib/libft

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/$(PARSE_DIR)/tokenize.c \
	$(SRC_DIR)/$(PARSE_DIR)/utils_cleanup.c \
	$(SRC_DIR)/$(PARSE_DIR)/utils_leftovers.c \

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell

ifneq ($(SHOW),1)
QUIET = @
endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(QUIET)make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIB_FLAGS) -o $(NAME)

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