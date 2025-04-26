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

int	word_token(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i + len])
	{
		if (input[i + len] == ' ')
			return (len);
		if (input[i + len] == '"' || input[i + len] == '\'')
			return (len);
		if (input[i + len] == '>'
			|| input[i + len] == '<'
			|| input[i + len] == '|')
			return (len);
		if (input[i + len] == '$')
			return (len);
		len++;
	}
	return (len);
}

int	variable_token(char *input, int i)
{
	int	len;

	len = 1;
	if (input[i + len] == '?')
		return (2);
	if (!ft_isalpha(input[i + len]) && input[i + len] != '_')
	{
		syntax_error("invalid character after $");
		return (0);
	}
	len++;
	while (ft_isalnum(input[i + len]) || input[i + len] == '_')
		len++;
	return (len);
}

int	quote_token(char *input, int i)
{
	char	quote;
	int		start;

	start = i;
	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
	{
		start = i - start + 1;
		return (start);
	}
	syntax_error("unclosed quote");
	return (0);
}

/* we tokenize with priority, ' or " is always highest priority
 * then would be # but not required by subject
 * then is $ which is fucking hard in bash but we only need to
 * take care of env expension which makes it easy-peasy-lemon-squeasy
 * then redirects
 * then pipes
 * then come words
 */
int	get_token_len(char *input, int i)
{
	if (!input || !input[i])
		return (0);
	if (input[i] == '\'' || input[i] == '"')
		return (quote_token(input, i));
	else if (input[i] == '$')
		return (variable_token(input, i));
	else if (input[i] == '>' || input[i] == '<')
	{
		if (input[i + 1] == input[i])
			return (2);
		return (1);
	}
	else if (input[i] == '|')
		return (1);
	else
		return (word_token(input, i));
	return (1);
}

char	*get_token(char *input, int *index)
{
	int		i;
	int		token_len;
	char	*token;

	i = *index;
	while (input[i] && is_space(input[i]))
		i++;
	if (!input[i])
	{
		*index = i;
		return (NULL);
	}
	token_len = get_token_len(input, i);
	if (token_len == 0)
		return (NULL);
	token = ft_substr(input, i, token_len);
	if (!token)
		return (NULL);
	*index = i + token_len;
	if (input[*index] && is_space(input[*index]))
		(*index)++;
	return (token);
}
