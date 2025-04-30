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

char	*token_word(char *input, size_t *i)
{
	size_t	start;

	start = *i;
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i])
		&& input[*i] != '\''
		&& input[*i] != '"'
		&& input[*i] != '#')
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

bool	is_heredoc(char *input, size_t *i)
{
	if (input[*i] == '<' && input[*i - 1] == '<')
		return (true);
	else
		return (false);
}

char	*token_operator(char *input, size_t *i)
{
	char	current_operator;
	char	*heredoc_input;

	current_operator = input[*i];
	(*i)++;
	if (input[*i] == current_operator)
	{
		if (is_heredoc(input, i) == true)
		{
			(*i)++;
			heredoc_input = token_heredoc(input, i);
			return (heredoc_input);
		}
		return ((*i)++, ft_substr(input, *i - 2, 2));
	}
	if (is_operator(input[*i]))
		syntax_error("unknown operator combination found");
	return (ft_substr(input, *i -1, 1));
}

// char *expand_var(char *input, size_t *i)
// {
// 	char	*path;
// 	char	*var_name;
// 	size_t	start;

// 	(*i)++;
// 	start = *i;
// 	if (input[*i] == '?')
// 		return (ft_itoa(0));
// 	while (ft_isalnum(input[*i]) || input[*i] == '_')
// 		(*i)++;
// 	if (start != *i)
// 	{
// 		var_name = ft_substr(input, start, *i - start);
// 		printf("%s", var_name);
// 		path = my_getenv(my_env, var_name);
// 		if (path)
// 			return (free(var_name), ft_strdup(path));
// 		else
// 			return (ft_strdup(""));
// 	}
// 	return (ft_strdup("$"));
// }

char	*token_get(char *input, size_t *i)
{
	if (!input[*i])
		return (NULL);
	else if (input[*i] == '\'' || input[*i] == '"')
		return (token_quote(input, i));
	else if (input[*i] == '#')
		return (NULL);
	else if (is_operator(input[*i]))
		return (token_operator(input, i));
	else
		return (token_word(input, i));
	return (NULL);
}
