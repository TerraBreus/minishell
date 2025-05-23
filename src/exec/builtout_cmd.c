#include "minishell.h"

int	builtout_cmd(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data)
{
	pid_t	pid;
	
	pid = fork();

	if (pid == -1)
		exit(EXIT_FAILURE);				//TODO Forking failure.
	if (pipe_data != NULL)
	{
		if (setup_pipe_builtout(pipe_data) == -1)	//TODO
			exit(EXIT_FAILURE);			//TODO dup2 failure.
	}
	if (setup_redir == -1)					//TODO
		exit(EXIT_FAILURE);				//dup2 failure
	if (pid == 0)
	{
		exec_cmd(cmd_list, shell_data->env_copy);	//TODO
		return (-1);
	}
	else
		return (0);


