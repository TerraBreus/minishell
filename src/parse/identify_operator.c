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

static int	get_operator_len(char *input, int i)
{
	if (input[i] == input[i + 1] && is_operator_char(input[i]))
		return (2);
	if (is_operator_char(input[i]))
		return (1);
	return (0);
}

int	get_operator(char *input, int i, int len)
{
	int	operator_len;

	operator_len = get_operator_len(input, i + len);
	if (operator_len)
	{
		if (len == 0)
			return (operator_len);
		else
			return (-1);
	}
	return (0);
}

static int	identify_operator(char *input, int i, int len)
{
	int	operator_result;

	if (is_space(input[i + len]))
		return (1);
	operator_result = get_operator(input, i, len);
	if (operator_result == -1)
		return (1);
	if (operator_result > 0)
		return (2);
	return (0);
}

int	handle_operator_case(char *input, int i, int len)
{
	int	result;

	result = identify_operator(input, i, len);
	if (result == 1)
		return (1);
	if (result == 2)
		return (get_operator_len(input, i + len));
	return (0);
}

t_token_type	get_operator_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strcmp(token, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(token, ">>") == 0)
		return (TOKEN_APPEND);
	return (TOKEN_WORD);
}
