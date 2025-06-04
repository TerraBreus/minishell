#include "minishell.h"

int	mult_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	t_pipe	pipe_data;
	int	last_pid;
	int	status;

	parse_mult_cmd(cmd_list);
	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
		{
			if (create_pipe(&pipe_data) == -1)
				exit(EXIT_FAILURE);								//TODO Close pipe_struct and exit on malloc/pipe failure
		}
		last_pid = builtin(shell_data, &cmd_list);
		if (last_pid == BUILTIN_NOT_FOUND)
			last_pid = builtout_cmd(cmd_list, shell_data, &pipe_data);
		else if (cmd_list->next == NULL)
			return (last_pid); //in this case we must return the exit status of the built in command.
		cmd_list = cmd_list->next;
	}
	return (ft_wait(last_pid, &status));
}
