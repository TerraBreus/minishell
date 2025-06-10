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

int	builtout_cmd(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pipe_data != NULL)
	{
		if (setup_pipe_builtout(pipe_data, pid, cmd_list->type) == -1)
			exit(EXIT_FAILURE);
	}
	if (setup_redir(cmd_list->redirection) == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		save_close_restore_io(CLOSE);
		exec_cmd(cmd_list->argv, shell_data->env);
		return (-1);
	}
	else
		return (pid);
}
