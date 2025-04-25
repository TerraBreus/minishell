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

// in bash nothing gets excecuted with syntax error, so delete all nodes
// and change first one to syntax error
void	quotes_aint_closed(t_list **token_list)
{
	t_list			*first_node;
	t_token_data	*error_data;

	if (!*token_list || !token_list)
		return ;
	first_node = *token_list;
	if (!first_node->content)
		return ;
	error_data = (t_token_data *)first_node->content;
	if (error_data->error)
		free(error_data->error);
	error_data->error = ft_strdup("QUOTES UNCLOSED");
	if (first_node->next != NULL)
	{
		ft_lstclear(&first_node->next, token_del);
		first_node->next = NULL;
	}
}

void	unclosed_quotes_check(t_list *token_list)
{
	char			*last_token;
	t_list			*last;
	t_token_data	*token_data;
	size_t			len;

	if (!token_list)
		return ;
	last = ft_lstlast(token_list);
	if (last == NULL || last->content == NULL)
		return ;
	token_data = (t_token_data *)last->content;
	if (token_data == NULL || token_data->token == NULL)
		return ;
	last_token = token_data->token;
	len = ft_strlen(last_token);
	if (len == 0)
		return ;
	if (len == 1 && (last_token[0] == '\'' || last_token[0] == '"'))
		quotes_aint_closed(&token_list);
	else if (last_token[0] == '\'' && last_token[len -1] != '\'')
		quotes_aint_closed(&token_list);
	else if (last_token[0] == '"' && last_token[len -1] != '"')
		quotes_aint_closed(&token_list);
}

// i think ill just make the first node
// into an error node saying what the error is
void	syntax_check(t_list *token_list)
{
	unclosed_quotes_check(token_list);
	// outfile_missing_check(token_list);
	// are_pipes_correct_check(token_list);
}
