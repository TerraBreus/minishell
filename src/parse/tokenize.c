/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:52:31 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_quotes(char c, bool *in_singles, bool *in_doubles)
{
	if (c == '\'' && !*in_doubles)
	{
		*in_singles = !*in_singles;
		return (true);
	}
	else if (c == '\"' && !*in_singles)
	{
		*in_doubles = !*in_doubles;
		return (true);
	}
	return (false);
}

static char	*get_token(char *input, int *index,
					bool *in_singles, bool *in_doubles)
{
	int		start;
	int		token_len;
	char	*token;

	skip_spaces(input, index);
	start = *index;
	while (input[*index] != '\0')
	{
		if (handle_quotes(input[*index], in_singles, in_doubles))
		{
			(*index) += 1;
			continue ;
		}
		if (input[*index] == ' '
			&& *in_singles == false
			&& *in_doubles == false)
			break ;
		(*index) += 1;
	}
	token_len = *index - start;
	token = ft_substr(input, start, token_len);
	if (input[*index] && !*in_doubles)
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

static t_list	*token_to_node(char *input, int *index,
	bool *in_singles, bool *in_doubles)
{
	char	*char_token;
	t_list	*token_node;

	char_token = get_token(input, index, in_singles, in_doubles);
	if (!char_token)
		return (NULL);
	token_node = create_node(char_token, *in_singles, *in_doubles);
	if (!token_node)
	{
		free(char_token);
		ft_lstclear(&token_node, token_del);
		return (NULL);
	}
	return (token_node);
}

t_list	*tokenize_input(char *input)
{
	t_list	*token_list;
	t_list	*token_node;
	int		index;
	bool	in_singles;
	bool	in_doubles;

	token_list = NULL;
	index = 0;
	in_singles = false;
	in_doubles = false;
	while (input[index])
	{
		token_node = token_to_node(input, &index, &in_singles, &in_doubles);
		if (!token_node)
		{
			ft_lstclear(&token_list, token_del);
			return (NULL);
		}
		ft_lstadd_back(&token_list, token_node);
	}
	return (token_list);
}
