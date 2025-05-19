#include "minishell.h"

void	child_slavery(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *plumb_box)
{
	static bool	first_cmd = true;

	if (cmd_list->next != NULL)
	{
		if (first_cmd == true)
		{
			first_cmd = false;
			if (setup_pipe_first_cmd(plumb_box) == -1)
				exit(EXIT_FAILURE);	//TODO
		}
		else
		{
			if (setup_pipe_middle_cmd(plumb_box) == -1)
				exit(EXIT_FAILURE);
		}
	}
	else
	{
		first_cmd = true;
		if (setup_pipe_last_cmd(plumb_box) == -1)
			exit(EXIT_FAILURE);
	}

	save_or_restore_io(CLOSE);
	//SOLELY FOR DEBUGGING!!!
	for (int fd = 0; fd < 1024; ++fd)
		if (fcntl(fd, F_GETFD) != -1)
			dprintf(2, "child has open fd: %d\n", fd);

	if (single_command(cmd_list, t_envp) == -1)
		exit(EXIT_FAILURE);	//TODO
}

