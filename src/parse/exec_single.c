/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:54:29 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:44 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_unknown(t_shell *shell)
{
	write(STDERR_FILENO, shell->tokens[0], ft_strlen(shell->tokens[0]));
	write(STDERR_FILENO, ": command not found\n", 21);
	shell->last_errno = SYNTAX_ERROR;
	shell->found_error = true;
}

void	exec_single(t_shell *shell, char **arg_list)
{
	if (!arg_list || !arg_list[0])
		return ;
	if (ft_strncmp(arg_list[0], "echo", 5) == 0)
		my_echo(arg_list);
	else if (ft_strncmp(arg_list[0], "cd", 3) == 0)
		my_cd(shell, arg_list);
	else if (ft_strncmp(arg_list[0], "export", 7) == 0)
		my_export(shell, arg_list[1]);
	else if (ft_strncmp(arg_list[0], "env", 4) == 0)
		my_env(shell);
	else if (ft_strchr(arg_list[0], '='))
		export_local(shell, arg_list[1]);
	else
		cmd_unknown(shell);
}
