/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:15:06 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 15:19:10 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// it took god 6 days to create the earth,
//  and 7 to create holy bash
#include "minishell.h"

static void	cmd_unknown(t_shell *shell)
{
	write(STDERR_FILENO, shell->tokens[0], ft_strlen(shell->tokens[0]));
	write(STDERR_FILENO, ": Command not found\n", 21);
	shell->last_errno = SYNTAX_ERROR;
	shell->found_error = true;
}

static void	dir_unknown(t_shell *shell)
{
	write(STDERR_FILENO, shell->tokens[0], ft_strlen(shell->tokens[0]));
	write(STDERR_FILENO, ": Is a directory\n", 18);
	shell->last_errno = DIR_PROMPT;
	shell->found_error = true;
}

static void	my_exit(t_shell *shell, t_cmd *exec)
{
	cleanup_env(shell);
	cleanup_shell(shell);
	cleanup_struct(&exec);
	exit(EXIT_SUCCESS);
}

// void	exec_single(t_shell *shell, char **arg_list, t_cmd **exec)
// {
// 	if (!arg_list || !arg_list[0])
// 		return ;
// 	if (ft_strncmp(arg_list[0], "echo", 5) == 0)
// 		my_echo(arg_list);
// 	else if (ft_strncmp(arg_list[0], "cd", 3) == 0)
// 		my_cd(shell, arg_list);
// 	else if (ft_strncmp(arg_list[0], "pwd", 4) == 0)
// 		my_pwd(shell);
// 	else if (ft_strncmp(arg_list[0], "export", 7) == 0)
// 		my_export(shell, arg_list);
// 	else if (ft_strncmp(arg_list[0], "env", 4) == 0)
// 		my_env(shell);
// 	else if (arg_list[0][0] == '/')
// 		dir_unknown(shell);
// 	else if (ft_strncmp(arg_list[0], "unset", 4) == 0)
// 		my_unset(shell, arg_list);
// 	else if (ft_strncmp(arg_list[0], "exit", 5) == 0)
// 		my_exit(shell, exec);
// 	else
// 		cmd_unknown(shell);
// }

void	builtin_cmd(t_shell *shell, t_cmd *exec)
{
	t_cmd	*current;

	current = exec;
	if (ft_strncmp(current->argv[0], "echo", 5) == 0)
		my_echo(current->argv);
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		my_cd(shell, current->argv);
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		my_pwd(shell);
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		my_export(shell, current->argv);
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		my_env(shell);
	else if (current->argv[0][0] == '/')
		dir_unknown(shell);
	else if (ft_strncmp(current->argv[0], "unset", 4) == 0)
		my_unset(shell, current->argv);
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		my_exit(shell, exec);
	else
		cmd_unknown(shell);
}
