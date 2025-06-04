/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parse_mult_cmd.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:23:52 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:23:55 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_mult_cmd(t_cmd *cmd_list)
{
	if (cmd_list != NULL)
	{
		cmd_list->type = FIRST;
		cmd_list = cmd_list->next;
		while (cmd_list->next != NULL)
		{
			cmd_list->type = MIDDLE;
			cmd_list = cmd_list->next;
		}
		cmd_list->type = LAST;
	}
}
