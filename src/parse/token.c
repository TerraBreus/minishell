/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:15:19 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 15:20:14 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_error(t_shell *shell)
{
	ft_putstr_fd("error: \
minishell: input couldnt be tokenized: `", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = 1;
}

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
void	tokenize_input(t_shell *shell, char *input)
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
		if (shell->found_error == true || i == start)
		{
			tokenize_error(shell);
			return ;
		}
		shell->tokens[shell->tc] = ft_substr(input, start, i - start);
		shell->tc++;
		skip_blank(input, &i);
	}
	shell->tokens[shell->tc] = NULL;
}
