#include "minishell.h"

int	count_commands(t_cmd *c)
{
	int	result;

	result = 0;
	while (c != NULL)
	{
		result++;
		c = c->next;
	}
	return (result);
}
