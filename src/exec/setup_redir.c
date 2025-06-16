/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   setup_redir.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:25:25 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:25:27 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redir(t_redir *redir_data)
{
	char					*filepath;
	static t_redir_handler	handlers[] = { 
		handle_in,
		handle_append,
		handle_out,
		handle_heredoc
	};

	while (redir_data != NULL)
	{
		filepath = redir_data->filename_path;
		if (filepath == NULL || *filepath == '\0')
			return (ft_putstr_fd("error: No such file\n", STDERR_FILENO),-1);
		if (check_file_permissions(filepath, redir_data->type) == -1)
			return (-1);
		if (redir_data->type < 0 || redir_data->type > 3)
			return (-1);
		if (handlers[redir_data->type](redir_data) == -1)
			return (-1);
		redir_data = redir_data->next;
	}
	return (0);
}
