#include "minishell.h"

void	exit_on_fail(t_shell *shell, t_cmd *cmd_list)
{
	ft_putstr_fd("Cleaning up on systemcall failure", 2);
	cleanup_env(shell);
	cleanup_shell(shell);
	cleanup_struct(&cmd_list);
	exit(EXIT_FAILURE);
}

