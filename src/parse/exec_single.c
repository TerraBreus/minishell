/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   And all the pieces matter...                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Me                                         +#+  +:+       +#+        */
/*       Shoutout to: Terry A. Davis              +#+#+#+#+#+   +#+           */
/*   Created: / 66:77:88 by The Chosen One             #+#    #+#             */
/*   Updated: / 66:77:88 by Me                        ###   ########.fr       */
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

void	exec_single(t_shell *shell, char **arg_list, t_cmd *exec)
{
	if (!arg_list || !arg_list[0])
		return ;
	if (ft_strncmp(arg_list[0], "echo", 5) == 0)
		my_echo(arg_list);
	else if (ft_strncmp(arg_list[0], "cd", 3) == 0)
		my_cd(shell, arg_list);
	else if (ft_strncmp(arg_list[0], "pwd", 4) == 0)
		my_pwd(shell);
	else if (ft_strncmp(arg_list[0], "export", 7) == 0)
		my_export(shell, arg_list);
	else if (ft_strncmp(arg_list[0], "env", 4) == 0)
		my_env(shell);
	else if (arg_list[0][0] == '/')
		dir_unknown(shell);
	else if (ft_strncmp(arg_list[0], "unset", 4) == 0)
		my_unset(shell, arg_list);
	else if (ft_strncmp(arg_list[0], "exit", 5) == 0)
		my_exit(shell, exec);
	else
		cmd_unknown(shell);
}
