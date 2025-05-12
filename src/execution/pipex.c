#include "minishell.h"

int	setup_last_read_end(int *last_read_end)
{
	if (dup2(*last_read_end, STDIN_FILENO) == -1)
	{
		close(*last_read_end);
		return (-1);
	}
	close(*last_read_end);
	*last_read_end = -1;
	return (0);
}

int	create_new_pipe(int *last_read_end)
{
	int	pipe_fd[2];

	if (*last_read_end != -1)
		setup_last_read_end(last_read_end);
	if (pipe(pipe_fd) == -1)
		return (-1);	//TODO Must I close last_read_end here or in exec_cmd_list?
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (-1);	//TODO Close the pipe?
	close(pipe_fd[1]);
	*last_read_end = pipe_fd[0];
	return (0);
}


