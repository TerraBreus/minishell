/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/10 14:19:11 by masmit           ###   ########.fr       */
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
	if (shell->found_error == true)
		return ;
	if (is_operator(shell->tokens[shell->tc -1][0])
		|| shell->tokens[0][0] == '|')
	{
		syntax_error(shell, &shell->tokens[i][0]);
		return ;
	}
	while (i < shell->tc -1
		&& shell->found_error == false)
	{
		if (shell->tokens[i][0] == '|'
			&& shell->tokens[i + 1][0] == '|')
			syntax_error(shell, &shell->tokens[i][0]);
		if (get_redir_type(shell->tokens[i]) != NONE
			&& (get_redir_type(shell->tokens[i + 1]) != NONE
				|| shell->tokens[i + 1][0] == '|'))
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
	sigquit(shell, input);
	sigint(shell);
	tokenize(shell, input);
	free(input);
	syntax_check(shell);
	if (shell->found_error == false)
	{
		expand_tokens(shell);
		shell->last_errno = 0;
		token_to_struct(shell, &exec);
		execution(exec, shell);
		cleanup_struct(&exec);
	}
	cleanup_shell(shell);
}
