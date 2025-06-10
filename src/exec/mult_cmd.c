/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   mult_cmd.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:23:45 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:23:47 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mult_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	t_pipe		pipe_data;
	int			last_pid;
	int			status;

	parse_mult_cmd(cmd_list);
	while (cmd_list != NULL)
	{
		if (cmd_list->next != NULL)
		{
			if (create_pipe(&pipe_data) == -1)
				return (internal_error());
		}
		last_pid = child_command(cmd_list, shell_data, &pipe_data);
		cmd_list = cmd_list->next;
	}
	return (ft_wait(last_pid, &status));
}
