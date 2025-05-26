#include "minishell.h"

int	setup_pipe_builtin(t_pipe *pipe_data, t_cmd_type type)
{
	if (type == FIRST)
	{
		if (dup2(pipe_data->pfd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->pfd[1]);
		pipe_data->lre = pipe_data->pfd[0];
	}
	else if (type == MIDDLE)
	{
		if (dup2(pipe_data->lre, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->lre);
		if (dup2(pipe_data->pfd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->pfd[1]);
		pipe_data->lre = pipe_data->pfd[0];
	}
	else if (type == LAST)
	{
		if (dup2(pipe_data->lre, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->lre);
		close(pipe_data->pfd[0]);
	}
	else
		return (-1);
	return (0);
}
