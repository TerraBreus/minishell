NAME			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -Iinc -Ilib/libft -g
LDFLAGS			:= -Llib/libft -lft -lreadline -lncurses

SRC_DIR			:= src
OBJ_DIR			:= obj
LIBFT_DIR		:= lib/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

BUILTIN_SRCS	:= \
				builtin_env.c \
				builtin_export.c \
				builtin_export_helper.c \
				builtin_echo.c \
				builtin_cd.c \
				builtin_unset.c \
				builtin_pwd.c

PARSE_SRCS		:= \
				init.c \
				error.c \
				loop_start.c \
				token_operator.c \
				token_quote.c \
				token_rest.c \
				cleanup_quotes.c \
				env_expand.c \
				cmd_struct.c \
				cmd_redir.c \
				cmd_print.c \
				cmd_clean.c \
				signal.c \
				utils.c \
				shell_cleanup.c \
				utils_bool.c

EXEC_SRCS		:= \
			   builtin_cmd.c \
			   builtout_cmd.c \
			   count_commands.c \
			   create_pipe.c \
			   exec_cmd.c \
			   execution.c \
			   is_built_in.c \
			   mult_cmd.c \
			   parse_mult_cmd.c \
			   redirection_handlers.c \
			   save_close_restore_io.c \
			   setup_pipe_builtout.c \
			   setup_redir.c \
			   single_cmd.c

SRCS			:= main.c \
				$(addprefix parse/,$(PARSE_SRCS)) \
				$(addprefix exec/,$(EXEC_SRCS)) \
				$(addprefix builtin/,$(BUILTIN_SRCS))

OBJS			:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIBFT):
	$(MAKE) -s -C $(LIBFT_DIR) bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "cleaned obj folder"
	@rm -rf $(OBJ_DIR)
	$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
