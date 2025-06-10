/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   check_4_heredoc.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:19:55 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:19:58 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_4_heredoc(t_shell *shell, t_cmd *cmd_list)
{
	t_redir	*temp;

	while (cmd_list != NULL)
	{
		temp = cmd_list->redirection;
		while (temp != NULL)
		{
			if (temp->type == HEREDOC)
			{
				if (setup_heredoc(shell, temp) == -1)
					return (-1);
			}
			temp = temp->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
