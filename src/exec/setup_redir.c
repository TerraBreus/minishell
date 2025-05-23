#include "minishell.h"

int	setup_redir(t_redir *redir_data)
{
	static t_redir_handler handlers[] = { 
		handle_in,
		handle_out,
		handle_append,
		handle_heredoc
	};

	while (redir_data != NULL)
	{
		if (redir_data->type < 0 || redir_data->type > 3)
			return (-1);
		if (handlers[redir_data->type](redir_data) == -1)
			return (-1);
		redir_data->next = redir_data;
	}
	return (0);
}
