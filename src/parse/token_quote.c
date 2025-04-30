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

// static size_t	expand_var_len(char	*path)
// {
// 	size_t	len;

// 	len = ft_strlen(path);
// 	free(path);
// 	return (len);
// }

static void	token_extension(char *input, size_t *i)
{
	while (input[*i]
		&& input[*i] != '\''
		&& input[*i] != '"'
		&& !is_space(input[*i])
		&& !is_operator(input[*i]))
		(*i)++;
}

static void	string_litteral(char *input, size_t *i)
{
	(*i)++;
	while (input[*i]
		&& input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
		(*i)++;
	else
		syntax_error("quotes unclosed");
	token_extension(input, i);
}

static void	string_interpolated(char *input, size_t *i)
{
	(*i)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
		(*i)++;
	else
		syntax_error("quotes unclosed");
	token_extension(input, i);
}

char	*token_quote(char *input, size_t *i)
{
	size_t	start;

	if (input[*i] && input[*i + 1])
	{
		start = *i;
		if (input[*i] == '\'')
		{
			string_litteral(input, i);
			return (ft_substr(input, start, *i - start));
		}
		else
		{
			start = *i;
			string_interpolated(input, i);
			return (ft_substr(input, start, *i - start));
		}
	}
	return (NULL);
}
