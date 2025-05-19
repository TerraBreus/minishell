#include "minishell.h"

int	setup_pipe_first_cmd(t_pipe *pipe_data)
{
	close(pipe_data->pfd[0]);
	if (dup2(pipe_data->pfd[1], STDOUT_FILENO) == -1)
		return (-1);
	close(pipe_data->pfd[1]);
	return (0);
}

int	setup_pipe_middle_cmd(t_pipe *pipe_data)
{
	if (dup2(pipe_data->last_read_end, STDIN_FILENO) == -1)
		return (-1);
	close(pipe_data->last_read_end);
	if (dup2(pipe_data->pfd[1], STDOUT_FILENO) == -1)
		return (-1);
	close(pipe_data->pfd[1]);
	return (0);
}

int	setup_pipe_last_cmd(t_pipe *pipe_data)
{
	if (dup2(pipe_data->last_read_end, STDIN_FILENO) == -1)
		return (-1);
	close(pipe_data->last_read_end);
	return (0);
}
