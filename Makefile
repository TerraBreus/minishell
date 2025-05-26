NAME			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -Iinc -Ilib/libft
LDFLAGS			:= -Llib/libft -lft -lreadline -lncurses

SRC_DIR			:= src
OBJ_DIR			:= obj
LIBFT_DIR		:= lib/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

BUILTIN_SRCS	:=

PARSE_SRCS		:=

EXEC_SRCS		:=

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