/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	shell_reset(t_shell *shell)
{
	g_signal = 0;
	shell->tc = 0;
	shell->found_error = false;
	shell->tokens = NULL;
}

static int	token_count_malloc(t_shell *shell, char *input)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(input)
		&& shell->found_error == false)
	{
		skip_space(input, &i);
		tokenize_input_len(shell, input, &i);
		shell->tc++;
	}
	shell->tokens = ft_calloc(shell->tc + 1, sizeof(char *));
	if (!shell->tokens)
	{
		malloc_fail(shell, "token count malloc");
		return (FAILURE);
	}
	shell->tc = 0;
	return (SUCCES);
}

// tc = token count
static void	tokenize_input(t_shell *shell, char *input)
{
	size_t	i;
	size_t	start;

	i = 0;
	if (is_input_empty(shell, input) == true)
		return ;
	add_history(input);
	skip_space(input, &i);
	if (token_count_malloc(shell, input) == FAILURE)
		return ;
	while (i < ft_strlen(input)
		&& shell->found_error == false)
	{
		start = i;
		tokenize_input_len(shell, input, &i);
		if (shell->found_error == true)
			return ;
		shell->tokens[shell->tc++] = ft_substr(input, start, i - start);
		skip_space(input, &i);
	}
	shell->tokens[shell->tc] = NULL;
}

void	is_it_ready(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->tc
		&& shell->found_error == false)
	{
		if (is_operator(shell->tokens[i][0]) == true
		&& (i == shell->tc - 1
		|| i == 0))
		{
			syntax_error(shell, &shell->tokens[i][0]);
			return ;
		}
		if (is_operator(shell->tokens[i][0])
			&& is_operator(shell->tokens[i + 1][0]))
			syntax_error(shell, &shell->tokens[i][0]);
		i++;
	}
}

void	loop(t_shell *shell)
{
	char	*input;

	setup_signals(shell);
	shell_reset(shell);
	input = readline("my_shell: ");
	sigquit(input);
	sigint(shell);
	tokenize_input(shell, input);
	free(input);
	is_it_ready(shell);
	if (shell->found_error == false)
	{
		expand_tokens(shell);
		cleanup_quotes(shell);
		exec_single(shell, shell->tokens);
	}
	cleanup_shell(shell);
}
