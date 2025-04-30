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

void	token_init(t_token_data *data)
{
	data->token = NULL;
	data->error = NULL;
	data->type = 0;
}

t_list	*create_node(char *token)
{
	t_list			*new_node;
	t_token_data	*data;

	data = malloc(sizeof(t_token_data));
	if (!data)
		return (NULL);
	token_init(data);
	data->token = token;
	new_node = ft_lstnew(data);
	return (new_node);
}

static t_list	*token_to_node(char *input, size_t *index)
{
	char	*char_token;
	t_list	*token_node;

	char_token = get_token(input, index);
	if (!char_token)
		return (NULL);
	token_node = create_node(char_token);
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
	size_t	index;

	token_list = NULL;
	index = 0;
	while (input[index] != '\0')
	{
		while (input[index] && is_space(input[index]))
			index++;
		if (input[index] == '\0')
			break ;
		token_node = token_to_node(input, &index);
		if (!token_node)
		{
			ft_lstclear(&token_list, token_del);
			return (NULL);
		}
		ft_lstadd_back(&token_list, token_node);
	}
	return (token_list);
}
