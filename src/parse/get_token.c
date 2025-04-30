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

char *operator_token(char *input, size_t *i)
{
	char current_operator;

	current_operator = input[*i];
	(*i)++;
	if (input[*i] == current_operator)
		return ((*i)++, ft_substr(input, *i - 2, 2));
	if (is_operator(input[*i]))
		syntax_error("unknown operator combination found");
	return (ft_substr(input, *i -1, 1));
}

char *expand_var(char *input, size_t *i)
{
	char	*path;
	char	*var_name;
	size_t	start;

	(*i)++;
	start = *i;
	if (input[*i] == '?')
		return (ft_itoa(0));
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (start != *i)
	{
		var_name = ft_substr(input, start, *i - start);
		printf("%s", var_name);
		path = getenv(var_name);
		if (path)
			return (free(var_name), ft_strdup(path));
		else
			return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}

char *word_token(char *input, size_t *i)
{
	size_t	start;
	bool	found_path;
	char	*input_with_path;

	start = *i;
	found_path = false;
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i])
		&& input[*i] != '\''
		&& input[*i] != '"'
		&& input[*i] != '#')
	{
		if (input[*i] == '$')
		{
			found_path = true;
			input_with_path = strjoin_and_free(
			ft_substr(&input[start], start, *i - start),
			expand_var(input, i));
		}
		(*i)++;
	}
	if (found_path)
		return (input_with_path);
	return (ft_substr(input, start, *i - start));
}

char	*get_token(char *input, size_t *i)
{
	if (!input[*i])
		return (NULL);
	else if (input[*i] == '\'' || input[*i] == '"')
		return (quote_token(input, i));
	else if (input[*i] == '#')
		return(NULL);
	else if (is_operator(input[*i]))
		return (operator_token(input, i));
	else if (input[*i] == '$')
		return (expand_var(input, i));
	else
		return (word_token(input, i));
	return (NULL);
}
