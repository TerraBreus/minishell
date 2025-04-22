# Tokenizer/input parser/exctract input
The tokenizer should basically make the following:

```c
echo "Hello   world" | grep world > out.txt
```

into 

```c
["echo", "Hello   world", "|", "grep", "world", ">", "out.txt"]
```

We can choose to make the tokenizer smarter by adding the enum-type to it. It then becomes a structure:

```c
typedef struct s_token
{
	char *str;
	enum type;
	struct s_token	*next;
	struct s_token	*prv;
}	t_token;
```

*I think writing a simple splitter that handles the quotation marks would be the smartest step and then later have it recognize what it is. Since you from the splitted array, you can easily convert it to a structure.*
