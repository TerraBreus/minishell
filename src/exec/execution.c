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
	int	cmd_c;
	int	error;

	save_close_restore_io(SAVE);
	error = check_4_heredoc(shell, cmd_list);
	if (error == NEW_PROMPT)
	{
		signals_init(shell);
		save_close_restore_io(RESTORE);
		return ;
	}
	if (error == -1)
		exit_on_fail(shell, cmd_list);
	cmd_c = count_commands(cmd_list);
	signal(SIGINT, SIG_IGN);
	if (cmd_c == 1)
		shell->last_errno = single_cmd(cmd_list, shell);
	else
		shell->last_errno = mult_cmd(cmd_list, shell);
	signals_init(shell);
	save_close_restore_io(RESTORE);
}
