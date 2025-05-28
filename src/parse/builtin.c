/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:34 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// it took god 6 days to create the earth,
//  and 7 to create holy bash
#include "minishell.h"

static int	dir_unknown(t_shell *shell)
{
	write(STDERR_FILENO, shell->tokens[0], ft_strlen(shell->tokens[0]));
	write(STDERR_FILENO, ": Is a directory\n", 18);
	shell->last_errno = DIR_PROMPT;
	shell->found_error = true;
	return (1);
}

static void	my_exit(t_shell *shell, t_cmd *exec)
{
	cleanup_env(shell);
	cleanup_shell(shell);
	cleanup_struct(&exec);
	exit(EXIT_SUCCESS);
}

int	builtin(t_shell *shell, t_cmd **exec)
{
	t_cmd	*current;

	if (shell->found_error == true)
		return (1);
	current = *exec;
	if (ft_strncmp(current->argv[0], "echo", 5) == 0)
		return (my_echo(current->argv));
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		return (my_cd(shell, current->argv));
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		return (my_pwd(shell));
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		return (my_export(shell, current->argv));
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		return (my_env(shell));
	else if (current->argv[0][0] == '/')
		return (dir_unknown(shell));
	else if (ft_strncmp(current->argv[0], "unset", 4) == 0)
		return (my_unset(shell, current->argv));
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		my_exit(shell, *exec);
	return (BUILTIN_NOT_FOUND);
}
