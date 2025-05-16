#include "minishell.h"
int	set_last_read_end(t_pipe *p)
{
	if (p->last_read_end != -1)
	{
		if (dup2(p->last_read_end, STDIN_FILENO) == -1)
			return (-1);		//TODO Close last_read_end probably?
		close(p->last_read_end);
		p->last_read_end = -1
	}
	return (0);
}