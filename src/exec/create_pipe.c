#include "minishell.h"

int	create_pipe(t_pipe *pipe_data)
{
	if (pipe(pipe_data->pfd) == -1)
		return (-1);
	else
		return (0);
}
