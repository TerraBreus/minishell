/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/07 14:23:42 by masmit           ###   ########.fr       */
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

bool	is_heredoc(char *str)
{
	if (!str)
		return (false);
	if (str[0] == '<' && str[1] == '<')
		return (true);
	else
		return (false);
}

// still need to let heredoc through as valid syntax but not rn
static void	syntax_check(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->tc
		&& shell->found_error == false)
	{
		if (is_operator(shell->tokens[i][0]) == true
		&& !is_heredoc(shell->tokens[i])
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
	sigquit(shell, input);
	sigint(shell);
	tokenize_input(shell, input);
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
