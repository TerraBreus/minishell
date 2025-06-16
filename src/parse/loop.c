/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/12 14:29:45 by masmit           ###   ########.fr       */
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

void	loop(t_shell *shell)
{
	char	*input;
	t_cmd	*exec;

	exec = NULL;
	shell_reset(shell);
	input = readline("my_shell: ");
	sigquit(shell, input);
	sigint(shell);
	tokenize(shell, input);
	free(input);
	syntax_check(shell);
	if (shell->found_error == false
		&& heredoc(shell, shell->tokens) != -1)
	{
		ambiguous_check(shell, shell->tokens);
		expand_tokens(shell);
		if (shell->found_error == false)
			shell->last_errno = 0;
		token_to_struct(shell, shell->tokens, &exec);
		print_exec(exec);
		execution(exec, shell);
		cleanup_struct(&exec);
	}
	cleanup_shell(shell);
}
