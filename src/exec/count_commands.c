/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   count_commands.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:20:07 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:20:08 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_cmd *cmd_list)
{
	int	result;

	result = 0;
	while (cmd_list != NULL)
	{
		result++;
		cmd_list = cmd_list->next;
	}
	return (result);
}
