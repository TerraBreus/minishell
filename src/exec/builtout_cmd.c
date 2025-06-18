/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtout_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:19:41 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/06 16:41:27 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtout_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_on_fail(shell_data, cmd_list, NULL, true);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (setup_redir(cmd_list->redirection) == -1)
			exit_on_fail(shell_data, cmd_list, NULL, false);
		save_close_restore_io(CLOSE);
		exec_cmd(cmd_list->argv, shell_data->env);
		return (-1);
	}
	else
	{
		close_heredoc_parent(cmd_list->redirection);
		//Check if we used a heredoc in this command and close it
		//by calling store_heredoc(-1) and closing it.
		return (pid);
	}
}
