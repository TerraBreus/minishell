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

int	g_signal;

static void	shell_reset(t_shell *shell)
{
	g_signal = 0;
	shell->tc = 0;
	shell->found_error = false;
	shell->tokens = NULL;
}

static void	syntax_check(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->tc
		&& shell->found_error == false)
	{
		if (is_operator(shell->tokens[i][0]) == true
		&& (i == shell->tc - 1 || i == 0))
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
	t_cmd	*exec;

	exec = NULL;
	shell_reset(shell);
	input = readline("my_shell: ");
	sigquit(input);
	sigint(shell);
	tokenize_input(shell, input);
	free(input);
	syntax_check(shell);
	if (shell->found_error == false)
	{
		expand_tokens(shell);
		shell->last_errno = 0;
		token_to_struct(shell, &exec);
		exec_single(shell, &exec);
		cleanup_struct(&exec);
	}
	cleanup_shell(shell);
}
