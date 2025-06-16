/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execution.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:23:15 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:23:17 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_cmd *cmd_list, t_shell *shell)
{
	int	cmd_count;

	cmd_count = 0;
	save_close_restore_io(SAVE);
	if (shell->found_error == true)
		return ;
	signal(SIGINT, SIG_IGN);
	cmd_count = count_commands(cmd_list);
	if (cmd_count == 0)
		return ;
	if (cmd_count == 1)
		single_cmd(cmd_list, shell);
	else
		mult_cmd(cmd_list, shell);
	signals_init(shell);
	save_close_restore_io(RESTORE);
}
