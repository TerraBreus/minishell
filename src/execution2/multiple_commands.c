#include "minishell.h"

int	multiple_commands(t_cmd *cmd_list, t_custom_envp *t_envp)
{
	t_pipe	*plumb_box;

	if (call_plumber(&plumb_box) == -1)
		return (-1);		//TODO Malloc failure. 
	
	while (cmd_list != NULL)
	{
		if (setup_last_read_end(plumb_box->last_read_end) == -1)
			exit(EXIT_FAILURE);
		if (cmd_list->next != NULL)
		{
			if (pipe(plumb_box->pfd) == -1)
				exit(EXIT_FAILURE);	//TODO Free pipe structure.
							//set write side of pipe to STDOUT.
			if (dup2(plumb_box->pfd[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);	//TODO Free close and exit.
			close(plumb_box->pfd[1]);
			plumb_box
		}
	}
}
