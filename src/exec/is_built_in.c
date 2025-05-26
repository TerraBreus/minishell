#include "minishell.h"

bool	is_built_in(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	if (ft_strncmp(current->argv[0], "my_echo", 8) == 0)	//TODO
		return (true);
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		return (true);
	/*
	else if (current->argv[0][0] == '/')
		dir_unknown(shell);
		return (true);
	*/
	else if (ft_strncmp(current->argv[0], "unset", 4) == 0)
		return (true);
	/*
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		my_exit(shell, *exec);
	*/
	else
		return (false);
}
