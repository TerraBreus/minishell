#include "minishell.h"

int	single_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	if (is_built_in(cmd_list) == true)
		builtin_cmd(shell_data, cmd_list, NULL);
	else
	{
		if (builtout_cmd(cmd_list, shell_data, NULL) == -1)
			exit(EXIT_FAILURE);				//TODO
		wait(NULL);						//TODO: retrieve exit status of child.
	}
	return (0);
}
