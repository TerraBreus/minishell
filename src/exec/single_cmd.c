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

	if (!cmd_list->argv)
		return (0);
	if (is_built_in(cmd_list) == true)
		return (builtin_cmd(shell_data, cmd_list));
	else
	{
		pid = builtout_cmd(cmd_list, shell_data, NULL);
		if (pid == -1)
			exit(EXIT_FAILURE);
		return (ft_wait(pid, &status));
	}
}
