/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   setup_pipe_builtin.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:25:04 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:25:06 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe_builtin(t_pipe *pipe_data, t_cmd_type type)
{
	if (type == FIRST)
	{
		if (dup2(pipe_data->pfd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->pfd[1]);
		pipe_data->lre = pipe_data->pfd[0];
	}
	else if (type == MIDDLE)
	{
		if (dup2(pipe_data->lre, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->lre);
		if (dup2(pipe_data->pfd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->pfd[1]);
		pipe_data->lre = pipe_data->pfd[0];
	}
	else if (type == LAST)
	{
		if (dup2(pipe_data->lre, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_data->lre);
		close(pipe_data->pfd[0]);
	}
	else
		return (-1);
	return (0);
}
