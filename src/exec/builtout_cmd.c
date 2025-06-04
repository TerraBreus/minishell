/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtout_cmd.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:19:41 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:19:44 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtout_cmd(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);				//TODO Forking failure.
	if (pipe_data != NULL)
	{
		if (setup_pipe_builtout(pipe_data, pid, cmd_list->type) == -1)
			exit(EXIT_FAILURE);			//TODO dup2 failure.
	}
	if (setup_redir(cmd_list->redirection) == -1)
		exit(EXIT_FAILURE);				//TODO dup2 failure
	if (pid == 0)
	{	
		signal(SIGINT, SIG_DFL);
		save_close_restore_io(CLOSE);
		exec_cmd(cmd_list->argv, shell_data->env);
		return (-1);
	}
	else
	{
		sigint_parent(shell_data, pid);
		return (pid);
	}
}