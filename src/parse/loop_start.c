/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:14:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	shell_reset(t_shell *shell)
{
	g_signal = 0;
	shell->tc = 0;
	shell->found_error = FALSE;
	shell->tokens = NULL;
}

static void	token_count_malloc(t_shell *shell, char *input)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(input)
		&& shell->found_error == FALSE)
	{
		skip_space(input, &i);
		tokenize_input_len(shell, input, &i);
		shell->tc++;
	}
	shell->tokens = ft_calloc(shell->tc + 1, sizeof(char *));
	if (!shell->tokens)
		malloc_fail(shell, "token count malloc");
	shell->tc = 0;
}

// tc = token count
static void	tokenize_input(t_shell *shell, char *input)
{
	size_t	i;
	size_t	start;

	i = 0;
	if (is_input_empty(shell, input) == TRUE)
		return ;
	add_history(input);
	skip_space(input, &i);
	token_count_malloc(shell, input);
	while (i < ft_strlen(input)
		&& shell->found_error == FALSE)
	{
		start = i;
		tokenize_input_len(shell, input, &i);
		if (shell->found_error == TRUE)
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
		&& shell->found_error == FALSE)
	{
		if (is_operator(shell->tokens[i][0]) == TRUE
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

	setup_signals();
	shell_reset(shell);
	input = readline("my_shell: ");
	ctrl_d(input);
	signal_is_int(shell);
	tokenize_input(shell, input);
	free(input);
	is_it_ready(shell);
	if (shell->found_error == FALSE)
	{
		expand_tokens(shell);
		print_tokens(shell);
	}
	cleanup_shell(shell);
}
