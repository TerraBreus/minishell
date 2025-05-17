#include "minishell.h"

int	temp_single_command(t_cmd *cmd_list, t_custom_env *envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		return (single_command(cmd_list, envp));
	return (0);
}
