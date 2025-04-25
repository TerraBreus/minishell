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

int	identify_quotes(char *input, int i, int *len)
{
	char	quote;
	int		index;

	index = i + 1;
	quote = input[i];
	while (input[index] && input[index] != quote)
		index++;
	if (input[index] == quote)
		*len = index - i + 1;
	else
		*len = index - i;
	return (*len);
}

int	handle_quoted_token(char *input, int i)
{
	int	quote_len;

	quote_len = 0;
	if (input[i] == '\'' || input[i] == '"')
	{
		identify_quotes(input, i, &quote_len);
		return (quote_len);
	}
	return (0);
}
