#include "minishell.h"

void	parse_mult_cmd(t_cmd *cmd_list)
{
	if (cmd_list != NULL)
	{
		cmd_list->type = FIRST;
		cmd_list = cmd_list->next;
		while (cmd_list->next != NULL)
		{
			cmd_list->type = MIDDLE;
			cmd_list = cmd_list->next;
		}
		cmd_list->type = LAST;
	}
}
