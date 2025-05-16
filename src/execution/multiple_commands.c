#include "minishell.h"

int	multiple_commands(t_cmd *cmd_list, t_custom_envp *t_envp)
{
	t_pipe	*plumb_box;
	pid_t	pid;

	plumb_box = NULL;
	if (init_pipe(&plumb_box) == -1)
		return (-1);		//TODO Malloc failure. 
	
	while (cmd_list != NULL)
	{
		//Bunch of piping stuff:
		if (set_last_read_end(plumb_box) == -1)	//TODO
			exit(EXIT_FAILURE);
		if (cmd_list->next != NULL)
		{
			if (pipe(plumb_box->pfd) == -1)
				exit(EXIT_FAILURE);	//TODO Free pipe structure.
							//set write side of pipe to STDOUT.
			if (dup2(plumb_box->pfd[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);	//TODO Free close and exit.
			close(plumb_box->pfd[1]);
			plumb_box->last_read_end = plumb_box->pfd[0];
		}
		
		//Actions differ between child and parent.
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);	//TODO: what must we do when forking fails?
		else if(pid == 0)
			child_slavery(cmd_list, t_envp);		//TODO: close all irrelevant fd's
		else
			adult_entertainment(cmd_list, t_envp); //TODO: close all irrelevant fd's
	
		cmd_list = cmd_list->next;
	}

	//At the end, we must wait for all child processes to finish
	while (wait(NULL) != -1)	//TODO: must save exitstatus of last child
		;
	return (0);
}
