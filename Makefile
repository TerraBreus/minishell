NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilib/libft

MINILIB_FLAGS = -lreadline -lncurses

SRC_DIR = src
PARSE_DIR = parse
EXEC_DIR = exec
LIBFT_DIR = lib/libft

PARSE_SRCS = \
	token_to_list.c \
	token_get.c \
	token_quote.c \
	token_label.c \
	token_expansion.c \
	token_heredoc.c \
	cmd_list_create.c \
	cmd_list_utils.c \
	cmd_list_print.c \
	cmd_list_cleanup.c \
	syntax_check.c \
	env_init.c \
	env_cmd.c \
	utils_cleanup.c \
	utils_leftovers.c

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

