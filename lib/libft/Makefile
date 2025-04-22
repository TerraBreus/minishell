
files =		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_strdup.c ft_calloc.c

bonus =		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

gnl =		../gnl/get_next_line.c ../gnl/get_next_line_utils.c

printf =	../ft_printf/ft_printf.c ../ft_printf/printBasics.c \
			../ft_printf/printHex.c ../ft_printf/printNumbers.c

Compiler = cc
CompilerFlags = -Wall -Werror -Wextra -g
libft_OFiles = $(files:.c=.o)
Bonus_OFiles = $(bonus:.c=.o)
GNL_OFiles = $(gnl:.c=.o)
Printf_OFiles = $(printf:.c=.o)

NAME = libft.a

$(NAME): $(libft_OFiles) $(GNL_OFiles) $(Printf_OFiles)
	ar rcs $(NAME) $(libft_OFiles) $(GNL_OFiles) $(Printf_OFiles)

bonus: $(libft_OFiles) $(Bonus_OFiles) $(GNL_OFiles) $(Printf_OFiles)
	ar rcs $(NAME) $(libft_OFiles) $(Bonus_OFiles) $(GNL_OFiles) $(Printf_OFiles)

%.o: %.c
	$(Compiler) $(CompilerFlags) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(libft_OFiles) $(Bonus_OFiles) $(GNL_OFiles) $(Printf_OFiles)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus