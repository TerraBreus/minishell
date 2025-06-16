/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   check_file_permissions.c                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/10 09:45:24 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/16 13:54:21 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_infile_perm(char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == 0)
			return (0);
		perror("Insufficient permissions:");
		return (-1);
	}
	ft_putstr_fd(filename, STDERR_FILENO);
	perror(": Infile not found");
	return (-1);
}

static int	check_outfile_perm(char *filename)
{
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) == 0)
			return (0);
		ft_putstr_fd(filename, STDERR_FILENO);
		perror(": Insufficient permissions");
		return (-1);
	}
	return (0);
}

int	check_file_permissions(char *filename, t_type type)
{
	if (type == APPEND || type == OUT)
		return (check_outfile_perm(filename));
	else if (type == IN)
		return (check_infile_perm(filename));
	else if (type == HEREDOC)
		return (0);
	write(2, "check_file_permission\n", 23);
	return (-1);
}
