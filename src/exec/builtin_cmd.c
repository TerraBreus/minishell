/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_cmd.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:19:19 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:19:26 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(t_shell *shell, t_cmd *cmd_list)
{
	if (setup_redir(cmd_list->redirection) == -1)
		return (1);
	return (builtin(shell, &cmd_list));
}
