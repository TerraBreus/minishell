#include "minishell.h"

int	single_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	int	pid;
	int	status;

	if (is_built_in(cmd_list) == true)
		return (builtin_cmd(shell_data, cmd_list, NULL));
	else
	{
		pid = builtout_cmd(cmd_list, shell_data, NULL);
		if (pid == -1)
			exit(EXIT_FAILURE);				//TODO
		return (ft_wait(pid, &status));
	}
}

/*
int	single_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	if (builtin(shell_data, &cmd_list) == BUILTIN_NOT_FOUND)
	{
		if (builtout_cmd(cmd_list, shell_data, NULL) == -1)
			exit(EXIT_FAILURE);				//TODO
		wait(NULL);							//TODO: retrieve exit status of child.
	}
	return (0);
}
*/
