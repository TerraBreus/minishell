#include "minishell.h"

typedef struct s_pipe
{
	int 	pfd[2];
	int	last_read_end;
}	t_pipe;

void	call_plumber(t_pipe **plumber)
{
	if (*plumber == NULL)
	{
		*plumber = (t_pipe *)malloc(sizeof(t_pipe));
		if (*plumber == NULL)
			exit(EXIT_FAILURE);				//TODO
	}
	pipe((*plumber)->pfd);
}

void	parental_control(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *plumber)
{
	static bool	first_time = true;

	if (first_time == true)
	{
		//close	write side
		//save	readside of pipe to last_read_end.
	}
	else if (cmd_list->next != NULL)
	{
		//close	last_read_end
		//close	write side pipe (p_fd[1])
		//save	read side of pipe (p_fd[0])
	}
	else
	{
		//close	last_read_end
	}
}

void	child_slavery(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *plumber)
{
	static bool	first_time = true;

	if (first_time == true)						//First child
	{
		//dup2	write side pipe (pfd[1]) to stdin
		//close	whole pipe
		first_time = false;
	}
	else if (cmd_list->next != NULL)				//Middle child
	{
		//dup2	last_read_end with stdin
		//close	last_read_end
		//dup2	write side pipe (pfd[1]) to stdin
		//close	whole pipe
	}
	else
	{
		//dup2	last_read_end with stdin
		//close	last_read_end
		first_time = true;
	}

}

int	exec_cmd_list(t_cmd *cmd_list, t_custom_env *t_envp)	//WORKS ONLY FOR NON BUILT IN COMMANDS!!! TODO
{
	pid_t		pid;
	t_pipe		*plumber;

	plumber = NULL;
	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
			call_plumber(&plumber);				//CREATE NEW PIPE

		pid = fork();
		if (pid == 0)
		{
			child_slavery(cmd_list, t_envp, plumber);
			setup_io(cmd_list->redirection);
			exec_cmd_in_child(cmd_list->argv, t_envp->env_copy, plumber->last_read_end);
		}
		else
			parental_control(cmd_list, t_envp, plumber);
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) != -1)
		;	//TODO Check erro for no_child
	return (0);
}

