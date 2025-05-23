#include "minishell.h"

static int	setup_pipe_for_child(t_pipe *pipe_data, t_cmd_type type)
{
	int	pipe_write;
	int	pipe_read;
	int	lre;

	pipe_write = pipe_data->pfd[1];
	pipe_read = pipe_data->pfd[0];
	lre = pipe_data->lre;

	save_close_restore_io(CLOSE);
	if (type == FIRST)
	{
		if (dup2(pipe_write, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);		//TODO dup2 failure. Close pipes etc.
	}
	else if (type == MIDDLE)
	{
		if (dup2(lre, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);		//TODO
		if (dup2(pipe_write, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	else if (type == LAST)
	{
		if (dup2(lre, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);		//TODO
	}
	else
		return (-1);

	close(lre);
	close(pipe_write);
	close(pipe_read);
	return (0);
}

int	setup_pipe_builtout(t_pipe *pipe_data, pid_t pid, t_cmd_type type)
{
	if (pid == 0)
		return (setup_pipe_for_child(pipe_data, type));
	else
	{
		if (type == FIRST)
		{
			close(pipe_data->pfd[1]);
			pipe_data->lre = pipe_data->pfd[0];
		}
		else if (type == MIDDLE)
		{
			close(pipe_data->lre);
			close(pipe_data->pfd[1]);
			pipe_data->lre = pipe_data->pfd[0];
		}
		else if (type == LAST)
		{
			close(pipe_data->lre);
		}
		else
			return (-1);
		return (0);
	}
}
