#include "minishell.h"

int	exec_cmd_list(t_cmd	*cmd_list, t_custom_env *t_envp)
{
	static int	last_read_end = -1;

	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
		{
			if (create_new_pipe(&last_read_end) == -1)
					exit(EXIT_FAILURE); //TODO Should really do closing of all the fd, freeing whatever we have (if applicable).
		}
		else
			setup_last_read_end(&last_read_end);
		setup_io(cmd_list->redirection);
		
//		if (built_in(*(cmd_list->argv)))	//TODO
//			exec_built_in(cmd_list);	//TODO
//		else
//			exec_cmd(cmd_list);
		exec_cmd_in_child(cmd_list->argv, t_envp->env_copy, last_read_end);
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) != -1)
		;	//TODO Check erro for no_child
	return (0);
}
