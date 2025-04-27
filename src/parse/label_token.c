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

void	label_the_tokens(void *content)
{
	t_token_data	*data;

	if (!content)
		return ;
	data = (t_token_data *)content;
	if (!data || !data->token)
		return ;
	if (ft_strcmp(data->token, ">") == 0)
		data->type = TOKEN_REDIRECT_OUT;
	else if (ft_strcmp(data->token, "<") == 0)
		data->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(data->token, ">>") == 0)
		data->type = TOKEN_APPEND;
	else if (ft_strcmp(data->token, "<<") == 0)
		data->type = TOKEN_HEREDOC;
	else if (ft_strcmp(data->token, "EOF") == 0)
		data->type = TOKEN_EOF;
	else if (ft_strcmp(data->token, "|") == 0)
		data->type = TOKEN_PIPE;
	else
		data->type = TOKEN_WORD;
}

void	expand_the_var(void *content)
{
	t_token_data	*data;
	char			*expanded;

	if (!content)
		return ;
	data = (t_token_data *)content;
	if (!data->token || data->type != TOKEN_WORD)
		return ;
	if (ft_strchr(data->token, '$') == NULL)
		return ;
	expanded = expand_token_var(data->token);
	if (!expanded)
		return ;
	free(data->token);
	data->token = expanded;
}

void	token_expansion(t_list *token_list)
{
	if (!token_list)
		return ;
	ft_lstiter(token_list, label_the_tokens);
	ft_lstiter(token_list, expand_the_var);
}
