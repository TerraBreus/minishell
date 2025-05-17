#include "minishell.h"

void	child_slavery(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *plumb_box)
{
	if (plumb_box->last_read_end != -1)
		close(plumb_box->last_read_end);
	
	save_or_restore_io(CLOSE);
	//SOLELY FOR DEBUGGING!!!
	for (int fd = 0; fd < 1024; ++fd)
		if (fcntl(fd, F_GETFD) != -1)
			dprintf(2, "child has open fd: %d\n", fd);

	if (single_command(cmd_list, t_envp) == -1)
		exit(EXIT_FAILURE);	//TODO
}

