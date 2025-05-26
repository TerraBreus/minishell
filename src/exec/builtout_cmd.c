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
		save_close_restore_io(CLOSE);
		exec_cmd(cmd_list->argv, shell_data->env_copy);
		return (-1);
	}
	else
		return (0);
}

