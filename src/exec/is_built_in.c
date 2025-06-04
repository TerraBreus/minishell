#include "minishell.h"

bool	is_built_in(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	if (!current->argv[0])
		return (false);
	if (ft_strncmp(current->argv[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		return (true);
	else if (current->argv[0][0] == '/')
		return (true);
	else if (ft_strncmp(current->argv[0], "unset", 4) == 0)
		return (true);
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		return (true);
	else
		return (false);
}
