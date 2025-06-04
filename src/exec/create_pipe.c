/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   create_pipe.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:20:19 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:20:21 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_pipe *pipe_data)
{
	if (pipe(pipe_data->pfd) == -1)
		return (-1);
	else
		return (0);
}
