NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilib/libft

MINILIB_FLAGS = -lreadline -lncurses

SRC_DIR = src
PARSE_DIR = parse
EXEC_DIR = exec
LIBFT_DIR = lib/libft

PARSE_SRCS = \
	init.c \
	error.c \
	loop_start.c \
	token_operator.c \
	token_quote.c \
	token_rest.c \
	env_cmd.c \
	env_expand.c \
	cleanup_quotes.c \
	cmd_struct.c \
	cmd_redir.c \
	cmd_print.c \
	signal.c \
	utils.c \
	utils_bool.c

EXEC_SRCS =

PARSE_SOURCES = $(addprefix $(PARSE_DIR)/,$(PARSE_SRCS))
EXEC_SOURCES = $(addprefix $(EXEC_DIR)/,$(EXEC_SRCS))

SRCS = \
	main.c \
	$(PARSE_SOURCES) \
	$(EXEC_SOURCES)

SRC_PATHS = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a

ifneq ($(SHOW),1)
QUIET = @
endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(QUIET)make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIB_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)rm -f $(OBJS)
	$(QUIET)make -C $(LIBFT_DIR) clean

fclean: clean
	$(QUIET)rm -f $(NAME)
	$(QUIET)make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean re fclean

