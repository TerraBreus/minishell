CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilib/libft

MINILIB_FLAGS = -lreadline -lncurses

SRC_DIR = src
PARSE_DIR = parse
LIBFT_DIR = lib/libft

PARSE_SRCS = \
    token_to_list.c \
    token_get.c \
    token_quote.c \
    token_label.c \
    token_expansion.c \
    token_heredoc.c \
    syntax_check.c \
    env_init.c \
	env_cmd.c \
    utils_cleanup.c \
    utils_leftovers.c

EXEC_SRCS = \

PARSE_SOURCES = $(addprefix $(SRC_DIR)/$(PARSE_DIR)/,$(PARSE_SRCS))
EXEC_SOURCES = $(addprefix $(SRC_DIR)/$(EXEC_DIR)/,$(EXEC_SRCS))

SRCS = \
    $(SRC_DIR)/main.c \
    $(PARSE_SOURCES) \
    $(EXEC_SOURCES)

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