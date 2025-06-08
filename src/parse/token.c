/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:41:56 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_malloc(t_shell *shell, char *input)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(input)
		&& shell->found_error == false)
	{
		skip_blank(input, &i);
		token_len(shell, input, &i);
		shell->tc++;
	}
	shell->tokens = ft_calloc(shell->tc + 1, sizeof(char *));
	if (!shell->tokens)
	{
		malloc_fail(shell, "token count malloc");
		return (FAILURE);
	}
	shell->tc = 0;
	return (SUCCESS);
}

// tc = token count
void	tokenize(t_shell *shell, char *input)
{
	size_t	i;
	size_t	start;

	i = 0;
	if (is_input_empty(shell, input) == true)
		return ;
	add_history(input);
	skip_blank(input, &i);
	if (token_malloc(shell, input) == FAILURE)
		return ;
	while (i < ft_strlen(input)
		&& shell->found_error == false)
	{
		start = i;
		token_len(shell, input, &i);
		shell->tokens[shell->tc++] = ft_substr(input, start, i - start);
		if (!shell->tokens[shell->tc -1])
			malloc_fail(shell, "tokenize");
		skip_blank(input, &i);
	}
	shell->tokens[shell->tc] = NULL;
}
