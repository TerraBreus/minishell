/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:25:32 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/06 16:41:38 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// can the return value be shell->last_errno?
// needed for siginterupt errno.
int	single_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	int	pid;
	int	status;

	if (is_built_in(cmd_list) == true)
		return (builtin_cmd(shell_data, cmd_list, NULL));
	else
	{
		pid = builtout_cmd(cmd_list, shell_data, NULL);
		if (pid == -1)
			exit(EXIT_FAILURE);				//TODO
		return (ft_wait(pid, &status));
	}
}

/*
int	single_cmd(t_cmd *cmd_list, t_shell *shell_data)
{
	if (builtin(shell_data, &cmd_list) == BUILTIN_NOT_FOUND)
	{
		if (builtout_cmd(cmd_list, shell_data, NULL) == -1)
			exit(EXIT_FAILURE);				//TODO
		wait(NULL);							//TODO: retrieve exit status of child.
	}
	return (0);
}
*/
