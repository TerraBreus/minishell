#include "minishell.h"

int	adult_entertainment(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *pipe_data)
{
	if (pipe_data->last_read_end != -1)
		close(pipe_data->last_read_end);
	if (cmd_list->next != NULL)
	{
		pipe_data->last_read_end = pipe_data->pfd[1];
		close(pipe_data->pfd[0]);
	}
	(void)cmd_list;
	(void)t_envp;
	return (0);
}
