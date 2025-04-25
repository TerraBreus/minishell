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

void	what_error(t_token_data *error_node, int errorno)
{
	if (errorno == SYNTAX_ERROR)
	{
		if (error_node->error)
			free(error_node->error);
		error_node->error = ft_strdup("syntax error");
	}
}

void	give_error(t_list **token_list, int errorno)
{
	t_list			*first_node;
	t_token_data	*error_data;

	if (!token_list || !*token_list)
		return ;
	first_node = *token_list;
	if (!first_node)
		return ;
	error_data = (t_token_data *)first_node->content;
	what_error(error_data, errorno);
}

static bool	is_redirect_valid(t_list *redirect)
{
	t_token_data	*next_data;

	if (!redirect->next)
		return (false);
	if (!redirect->next->content)
		return (false);
	next_data = (t_token_data *)redirect->next->content;
	if (!next_data)
		return (false);
	if (next_data->type != TOKEN_WORD)
		return (false);
	return (true);
}

void	outfile_missing_check(t_list *token_list)
{
	t_list			*current;
	t_token_data	*data;

	if (!token_list)
		return ;
	current = token_list;
	while (current)
	{
		if (current->content)
		{
			data = (t_token_data *)current->content;
			if (data->type == TOKEN_REDIRECT_OUT || data->type == TOKEN_APPEND)
			{
				if (!is_redirect_valid(current))
					give_error(&token_list, SYNTAX_ERROR);
			}
		}
		current = current->next;
	}
}
