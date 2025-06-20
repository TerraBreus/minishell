NAME			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -Iinc -Ilib/libft -g
LDFLAGS			:= -Llib/libft -lft -lreadline -lncurses

SRC_DIR			:= src
BIN_DIR			:= bin
LIBFT_DIR		:= lib/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

BUILTIN_SRCS	:= \
				builtin.c \
				builtin_cd.c \
				builtin_pwd.c \
				builtin_env.c \
				builtin_echo.c \
				builtin_unset.c \
				builtin_export.c \
				builtin_export_helper.c

PARSE_SRCS		:= \
				init.c \
				error.c \
				loop.c \
				token.c \
				token_len.c \
				syntax.c \
				rm_empty.c \
				rm_quotes.c \
				env_expand.c \
				cmd_struct.c \
				cmd_node.c \
				cmd_clean.c \
				cmd_print.c \
				signal.c \
				free.c \
				utils.c \
				utils_bool.c

EXEC_SRCS		:= \
				builtin_cmd.c \
				builtout_cmd.c \
				store_heredoc.c \
				check_4_heredoc.c \
				check_file_permissions.c \
				child_command.c \
				paths_for_execve.c \
				count_commands.c \
				create_pipe.c \
				exec_cmd.c \
				execution.c \
				ft_wait.c \
				close_pipe.c \
				is_built_in.c \
				mult_cmd.c \
				parse_mult_cmd.c \
				redirection_handlers.c \
				save_close_restore_io.c \
				setup_heredoc.c \
				run_heredoc.c \
				setup_pipe_builtout.c \
				setup_redir.c \
				single_cmd.c \
				exit_on_fail.c

SRCS			:= main.c \
				$(addprefix parse/,$(PARSE_SRCS)) \
				$(addprefix exec/,$(EXEC_SRCS)) \
				$(addprefix builtin/,$(BUILTIN_SRCS))

BIN				:= $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))

all:			$(LIBFT) $(NAME)

$(NAME):		$(BIN) $(LIBFT)
					@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIBFT):
				$(MAKE) -s -C $(LIBFT_DIR) bonus

$(BIN_DIR)/%.o:	$(SRC_DIR)/%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@echo "cleaned bin folder"
				@rm -rf $(BIN_DIR)
				$(MAKE) -s -C $(LIBFT_DIR) clean

fclean:			clean
					@rm -f $(NAME)
					$(MAKE) -s -C $(LIBFT_DIR) fclean

re:				fclean all

.PHONY:			all clean fclean re
