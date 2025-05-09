files =	ft_printf \
		printHex \
		printBasics \
		printNumbers \

Compiler = cc
CFLAGS = -Wall -Werror -Wextra -g
CFILES = $(files:%=%.c)
OFILES = $(files:%=%.o)
NAME = libftprintf.a

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)

%.o: %.c
	$(Compiler) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re