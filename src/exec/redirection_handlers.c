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

int	handle_in(t_redir *r)
{
	int		fd_in;

	if (check_file_permissions(r->filename_path, r->type) == -1)
		return (0);
	fd_in = open(r->filename_path, O_RDONLY);
	if (fd_in == -1)
		return (-1);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (-1);
	close(fd_in);
	return (0);
}

int	handle_out(t_redir *r)
{
	int		fd_out;

	if (check_file_permissions(r->filename_path, r->type) == -1)
		return (0);
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

	if (check_file_permissions(r->filename_path, r->type) == -1)
		return (0);
	fd_append = open(r->filename_path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd_append == -1)
		return (-1);
	if (dup2(fd_append, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_append);
	return (0);
}

int	handle_heredoc(t_redir *r)
{
	r->heredoc_fd = store_heredoc(-1);
	if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
		return (-1);
	close(r->heredoc_fd);
	return (0);
}
