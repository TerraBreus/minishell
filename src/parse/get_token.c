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

static int	process_normal_char(char *input, int i, int *len)
{
	if (is_space(input[i + *len]))
		return (1);
	if (input[i + *len] == '\'' || input[i + *len] == '"')
	{
		if (*len > 0)
			return (1);
		*len += handle_quoted_token(input, i + *len);
		return (2);
	}
	return (0);
}

int	get_token_len(char *input, int i)
{
	int	len;
	int	result;

	len = 0;
	result = handle_quoted_token(input, i);
	if (result > 0)
		return (result);
	while (input[i + len])
	{
		result = process_normal_char(input, i, &len);
		if (result == 1)
			break ;
		if (result == 2)
			return (len);
		result = handle_operator_case(input, i, len);
		if (result > 0)
			return (result);
		len++;
	}
	return (len);
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
	token = ft_substr(input, i, token_len);
	if (!token)
		return (NULL);
	*index = i + token_len;
	if (!is_operator_char(input[i]) && input[*index] && is_space(input[*index]))
		(*index)++;
	return (token);
}
