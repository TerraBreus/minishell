/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:25:32 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/11 16:03:40 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	int	pid;
	int	status;

	if (is_built_in(cmd_list) == true)
		return (builtin_cmd(shell_data, cmd_list));
	else
	{
		pid = builtout_cmd(cmd_list, shell_data);
		if (pid == -1)
			exit_on_fail(shell_data, cmd_list, NULL, false);
		return (ft_wait(shell_data, pid, &status));
	}
}
