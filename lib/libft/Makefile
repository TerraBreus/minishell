CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I. -I../gnl -I../ft_printf

LIBFT_SRCS = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_strdup.c ft_calloc.c \
	ft_strcmp.c ft_isspace.c ft_strjoin_free.c ft_strjoin_char.c \
	ft_realloc.c ft_strstr.c ft_leak.c ft_lstiter_param.c ft_filename.c \
	ft_bubble.c

BONUS_SRCS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

GNL_SRCS = \
	../gnl/get_next_line.c \
	../gnl/get_next_line_utils.c

PRINTF_SRCS = \
	../ft_printf/ft_printf.c \
	../ft_printf/printBasics.c \
	../ft_printf/printHex.c \
	../ft_printf/printNumbers.c

LIBFT_OBJ = $(LIBFT_SRCS:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)
GNL_OBJ = $(notdir $(GNL_SRCS:.c=.o))
PRINTF_OBJ = $(notdir $(PRINTF_SRCS:.c=.o))

ALL_OBJ =	$(PRINTF_OBJ) \
			$(LIBFT_OBJ) \
			$(BONUS_OBJ) \
			$(GNL_OBJ)

NAME = libft.a

VPATH = ../gnl:../ft_printf

all: $(NAME)

$(NAME): $(ALL_OBJ)
	ar rcs $@ $^

bonus: $(ALL_OBJ)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(ALL_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
