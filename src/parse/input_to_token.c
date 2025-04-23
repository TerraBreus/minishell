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

static bool	is_operator_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

static int	get_operator_len(char *input, int i)
{
	if (input[i] == input[i + 1] && is_operator_char(input[i]))
		return (2);
	if (is_operator_char(input[i]))
		return (1);
	return (0);
}

static int	handle_quotes(char *input, int i,
					bool *in_singles, bool *in_doubles)
{
	if (input[i] == '\'' && !(*in_doubles))
		*in_singles = !(*in_singles);
	else if (input[i] == '\"' && !(*in_singles))
		*in_doubles = !(*in_doubles);
	return (1);
}

static int	get_token_len(char *input, int i,
					bool *in_singles, bool *in_doubles)
{
	int	len;
	int	operator_len;

	len = 0;
	while (input[i + len] && (!is_space(input[i + len])
			|| *in_singles || *in_doubles))
	{
		operator_len = 0;
		if (!*in_singles && !*in_doubles)
		{
			operator_len = get_operator_len(input, i + len);
			if (operator_len && len == 0)
				return (operator_len);
			if (operator_len && len > 0)
				break ;
		}
		len += handle_quotes(input, i + len, in_singles, in_doubles);
		if ((!input[i + len] || is_space(input[i + len]))
			&& !*in_singles && !*in_doubles)
			break ;
		if (!operator_len)
			len++;
	}
	return (len);
}

char	*get_token(char *input, int *index, bool *in_singles, bool *in_doubles)
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
	token_len = get_token_len(input, i, in_singles, in_doubles);
	token = ft_substr(input, i, token_len);
	if (!token)
		return (NULL);
	*index = i + token_len;
	if (!is_operator_char(input[i]) && input[*index] && is_space(input[*index]))
		(*index)++;
	return (token);
}
