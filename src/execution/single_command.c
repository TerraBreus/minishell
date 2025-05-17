#include "minishell.h"

int	single_command(t_cmd *cmd_list, t_custom_env *t_envp)
{
//Setup redirection.
	if (set_redirection(cmd_list->redirection) == -1)
		return (-1);
	if (cmd_list->argv != NULL)
	{
		if (exec_cmd(cmd_list->argv, t_envp->env_copy) == -1)
			return (-1);
	}
	return (0);
}
