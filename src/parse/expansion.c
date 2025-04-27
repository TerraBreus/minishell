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

void	handle_quotes(char *token, size_t *i, int *in_doubles)
{
	if (token[*i] == '\'' && !*in_doubles)
	{
		(*i)++;
		while (token[*i] && token[*i] != '\'')
			(*i)++;
		return ;
	}
	if (token[*i] == '"')
	{
		*in_doubles = !*in_doubles;
		(*i)++;
	}
}

// TODO return value after ? should point to exit status of last prompt
char	*expand_variable(char *var_name)
{
	char	*value;

	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(0));
	value = getenv(var_name);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*var_to_path(const char *token, size_t *pos)
{
	size_t	start;
	char	*var_name;
	char	*expanded;

	(*pos)++;
	start = *pos;
	while (token[*pos] && (ft_isalnum(token[*pos]) || token[*pos] == '_'))
		(*pos)++;
	var_name = ft_substr(token, start, *pos - start);
	if (!var_name)
		return (NULL);
	expanded = expand_variable(var_name);
	free(var_name);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*process_token_characters(
	char *token, char *result, size_t *pos, int *in_doubles)
{
	char	*expanded;

	while (token[*pos])
	{
		handle_quotes(token, pos, in_doubles);
		if (!token[*pos])
			break ;
		else if (token[*pos] == '$' && token[*pos + 1])
		{
			expanded = var_to_path(token, pos);
			if (!expanded)
				return (NULL);
			result = strjoin_and_free(result, expanded);
			continue ;
		}
		else
			result = strjoin_char_and_free(result, token[*pos]);
		(*pos)++;
	}
	return (result);
}

char	*expand_token_var(char *token)
{
	char	*result;
	size_t	pos;
	int		in_doubles;

	result = ft_strdup("");
	if (!token || !result)
		return (free(result), NULL);
	pos = 0;
	in_doubles = false;
	result = process_token_characters(token, result, &pos, &in_doubles);
	if (!result)
		return (NULL);
	return (result);
}
