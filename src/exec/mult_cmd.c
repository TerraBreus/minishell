#include "minishell.h"

int	mult_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	t_pipe	pipe_data;

	parse_mult_cmd(cmd_list);

	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
		{
			if (create_pipe((&pipe_data)->pfd) == -1)	//TODO Create pipe
				exit(EXIT_FAILURE);			//TODO Close pipe_struct and exit on malloc/pipe failure
		}
		/*
		if (is_built_in(cmd_list->built_in))			//TODO
			builtin_cmd(cmd_list, shell_data,&pipe_data);		//TODO
		else
			builtout_cmd(cmd_list, shell_data, &pipe_data);		//TODO
		*/
		builtout_cmd(cmd_list, shell_data, &pipe_data);
	}
}
