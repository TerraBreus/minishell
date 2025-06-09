#include "minishell.h"

int	child_command(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (internal_error());
	if (setup_pipe_builtout(pipe_data, pid, cmd_list->type) == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		save_close_restore_io(CLOSE);
		if (setup_redir(cmd_list->redirection) == -1)
			exit (EXIT_FAILURE);
		if (is_built_in(cmd_list) == true)
			exit(builtin(shell_data, &cmd_list));
		else
			exec_cmd(cmd_list->argv, shell_data->env);
		exit(EXIT_FAILURE);
	}
	else
		return (pid);
}
