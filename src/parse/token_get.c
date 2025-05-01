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
	if (start != *i)
		return (ft_substr(input, start, *i - start));
	return (NULL);
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
