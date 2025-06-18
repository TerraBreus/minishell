#include "minishell.h"

int	store_heredoc(int pipe_read)
{
	static int	buffer[200];
	static bool	first_time = true;
	int		i;
	int		result;

	if (pipe_read == CLOSE)
		first_time = true;
	else if (pipe_read > 0)
	{
		if (first_time == true)
		{
			i = -1;
			while (++i < 200)
				buffer[i] = -2;
			first_time = false;
		}
		i = 0;
		while (buffer[i] != -2)
			i++;
		buffer[i] = pipe_read;
	}
	else
	{
		i = 0;
		while (buffer[i] == -3)
			i++;
		result = buffer[i];
		buffer[i] = -3;
		return (result);
	}
	return (0);
}

void	close_heredoc_parent(t_redir *r)
{
	int	fd;
	
	while(r != NULL)
	{
		if (r->type == HEREDOC)
		{
			fd = store_heredoc(-1);
			close(fd);
		}
		r = r->next;
	}
}

