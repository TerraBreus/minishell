#include "minishell.h"

int	count_commands(t_cmd *cmd_list)
{
	int	result;

	result = 0;

	while (cmd_list != NULL)
	{
		result++;
		cmd_list = cmd_list->next;
	}
	return (result);
}
