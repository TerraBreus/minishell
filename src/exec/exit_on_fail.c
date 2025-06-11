/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exit_on_fail.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/10 13:55:10 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/10 13:55:23 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_on_fail(t_shell *shell, t_cmd *cmd_list, bool print_error)
{
	if (print_error == true)
		perror("minishell");
	ft_putstr_fd("Cleaning up on systemcall failure\n", 2);
	if (shell != NULL)
	{
		cleanup_env(shell);
		cleanup_shell(shell);
	}
	if (cmd_list != NULL)
		cleanup_struct(&cmd_list);
	exit(EXIT_FAILURE);
}
