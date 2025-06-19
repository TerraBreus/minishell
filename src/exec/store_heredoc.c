/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   store_heredoc.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 16:13:29 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/19 16:13:30 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_first_fd(int buffer[], int i)
{
	int	result;

	while (buffer[i] == -3)
		i++;
	result = buffer[i];
	buffer[i] = -3;
	return (result);
}

void	clean_buffer(int buffer[], int i, bool *first_time)
{
	while (++i < 200)
		buffer[i] = -2;
	*first_time = false;
}

int	store_heredoc(int pipe_read)
{
	static int	buffer[200];
	static bool	first_time = true;
	int			i;

	if (pipe_read == CLOSE)
		first_time = true;
	else if (pipe_read > 0)
	{
		if (first_time == true)
			clean_buffer(buffer, -1, &first_time);
		i = 0;
		while (buffer[i] != -2)
			i++;
		buffer[i] = pipe_read;
	}
	else
		return (return_first_fd(buffer, 0));
	return (0);
}

void	close_heredoc_parent(t_redir *r)
{
	int	fd;

	while (r != NULL)
	{
		if (r->type == HEREDOC)
		{
			fd = store_heredoc(-1);
			close(fd);
		}
		r = r->next;
	}
}
