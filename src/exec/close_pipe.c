/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   close_pipe.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/11 12:28:04 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/11 12:28:06 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_pipe *pipe_data)
{
	close(pipe_data->lre);
	close(pipe_data->pfd[1]);
	close(pipe_data->pfd[0]);
}
