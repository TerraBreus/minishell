/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:05:09 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_path(char *token)
{
	size_t	i;

	i = 0;
	skip_litteral(token, &i);
	if (!token || !token[i])
		return (false);
	while (token[i])
	{
		if (token[i] == '$'
			&& (token[i + 1] == '_'
				|| token[i + 1] == '?'
				|| ft_isalnum(token[i + 1])))
			return (true);
		i++;
	}
	return (false);
}

void	token_var_to_path(void *content, void *my_env)
{
	t_token_data	*data;
	char			*new_token;

	(void)my_env;
	new_token = NULL;
	if (!content)
		return ;
	data = (t_token_data *)content;
	if (!data
		|| !data->token
		|| data->type != TOKEN_WORD_WITH_PATH)
		return ;
	if (has_path(data->token) == true)
		new_token = insert_path(data->token, my_env);
	free(data->token);
	data->token = new_token;
}

void	token_label(void *content)
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
	else if (ft_strcmp(data->token, "|") == 0)
		data->type = TOKEN_PIPE;
	else
	{
		if (has_path(data->token))
			data->type = TOKEN_WORD_WITH_PATH;
		else
			data->type = TOKEN_WORD;
	}
}

// removes newlines from heredoc tokens
void	token_clean_heredoc(void *content)
{
	t_token_data	*data;

	if (!content)
		return ;
	data = (t_token_data *)content;
	if (!data || !data->token)
		return ;
}

void	token_expansion(t_list *token_list, t_custom_env *env)
{
	if (!token_list)
		return ;
	ft_lstiter(token_list, token_label);
	ft_lstiter(token_list, token_clean_heredoc);
	ft_lstiter_param(token_list, token_var_to_path, env);
}
