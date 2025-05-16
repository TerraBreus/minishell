NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Iinc -Ilib/libft
LDFLAGS     := -lreadline -lncurses

SRC_DIR     := src
OBJ_DIR     := obj
LIBFT_DIR   := lib/libft
LIBFT       := $(LIBFT_DIR)/libft.a

PARSE_SRCS = \
	init.c \
	error.c \
	loop_start.c \
	token_operator.c \
	token_quote.c \
	token_rest.c \
	builtin_env.c \
	builtin_export.c \
	export_print.c \
	builtin_local.c \
	builtin_echo.c \
	builtin_cd.c \
	builtin_unset.c \
	env_expand.c \
	cleanup_quotes.c \
	cmd_struct.c \
	cmd_redir.c \
	cmd_print.c \
	signal.c \
	utils.c \
	utils_bool1.c \
	utils_bool2.c \
	exec_single.c

EXEC_SRCS   := 

SRCS        := main.c \
                $(addprefix parse/,$(PARSE_SRCS)) \
                $(addprefix exec/,$(EXEC_SRCS))
OBJS        := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

ifneq ($(SHOW),1)
QUIET       := @
endif

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(QUIET)$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIBFT):
	$(QUIET)$(MAKE) -s -C $(LIBFT_DIR) bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "cleaned obj folder"
	$(QUIET)rm -rf $(OBJ_DIR)
	$(QUIET)$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	$(QUIET)rm -f $(NAME)
	$(QUIET)$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re