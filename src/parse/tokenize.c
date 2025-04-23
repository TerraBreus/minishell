#include "minishell.h"

static void	skip_spaces(char *input, int *index)
{
	while (input[*index] && input[*index] == ' ')
		(*index) += 1;
}

static char	*get_token(char *input, int *index, bool *in_singles, bool *in_doubles)
{
	int		start;
	int		token_len;
	char	*token;

	start = *index;
	while (input[*index] != '\0')
	{
		if (input[*index] == '\'' && in_singles == false)
			*in_singles = true;
		else if (input[*index] == '\'' && in_doubles == false)
			*in_doubles = true;
		else if (input[*index] != ' ' && in_singles == false && in_doubles == false)
			break ;
		(*index) += 1;
	}
	token_len = *index - start;
	token = ft_substr(input, start, token_len);
	if (in_singles == false && in_doubles == false)
		skip_spaces(input, index);
	return (token);
}

t_list	*create_node(char *token, bool in_singles, bool in_doubles)
{
	t_list			*new_node;
	t_token_data	*data;

	data = malloc(sizeof(t_token_data));
	if (!data)
		return (NULL);
	data->token = token;
	data->in_singles = in_singles;
	data->in_doubles = in_doubles;
	new_node = ft_lstnew(data);
	return (new_node);
}

void	make_vars_zero(char **token, int *index, bool *in_singles, bool *in_doubles)
{
	*token = NULL;
	*index = 0;
	*in_singles = false;
	*in_doubles = false;
}

void    token_del(void *content)
{
	t_list *data;
	data = (t_list *)content;
	if (data)
	{
		free(data->content);
		free(data);
	}
}

t_list	*tokenize_input(char *input)
{
	t_list	*token_list;
	t_list	*token_node;
	char	*token;
	int		index;
	bool	in_singles;
	bool	in_doubles;

	token_list = NULL;
	make_vars_zero(&token, &index, &in_singles, &in_doubles);
	while (input[index])
	{
		token = get_token(input, &index, &in_singles, &in_doubles);
		if (!token)
		{
			ft_lstclear(&token_list, token_del);
			return (NULL);
		}
		free(input);
		token_node = create_node(token, in_singles, in_doubles);
		if (!token_node)
		{
			free(token);
			ft_lstclear(&token_list, token_del);
			return (NULL);
		}
		ft_lstadd_back(&token_list, (t_list *)token_node);
	}
	return (token_list);
}
