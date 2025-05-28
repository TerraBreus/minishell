#include "minishell.h"

int	mult_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	t_pipe	pipe_data;

	parse_mult_cmd(cmd_list);

	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
		{
			if (create_pipe(&pipe_data) == -1)
				exit(EXIT_FAILURE);								//TODO Close pipe_struct and exit on malloc/pipe failure
		}
		if (builtin(shell_data, &cmd_list) == BUILTIN_NOT_FOUND)
			builtout_cmd(cmd_list, shell_data, &pipe_data);		//IN PROGRESS
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) != -1)									//TODO
		;
	return (0);
}
