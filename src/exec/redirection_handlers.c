/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   redirection_handlers.c                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:24:00 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:24:01 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Check for file permissions when opening 
//(and print error message when insufficient permissions)

int	handle_in(t_redir *r)
{
	int		fd_in;

	fd_in = open(r->filename_path, O_RDONLY);
	if (fd_in == -1)
		return (-1);	//Would be useful to print error message of strerrno;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (-1);
	close(fd_in);
	return (0);
}

int	handle_out(t_redir *r)
{
	int		fd_out;

	fd_out = open(r->filename_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		return (-1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_out);
	return (0);
}

int	handle_append(t_redir *r)
{
	int		fd_append;

	fd_append = open(r->filename_path, O_WRONLY | O_CREAT, 0777);
	if (fd_append == -1)
		return (-1);
	if (dup2(fd_append, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_append);
	return (0);
}

int handle_heredoc(t_redir *r)
{
	if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
		return (-1);
	close(r->heredoc_fd);
	return (0);
}
