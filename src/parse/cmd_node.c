/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:57:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/16 12:58:08 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_back(t_cmd **exec, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!*exec)
	{
		*exec = new_cmd;
		return ;
	}
	temp = *exec;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
}

t_cmd	*new_node(t_shell *shell)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		malloc_fail(shell, "new command");
		return (NULL);
	}
	new_cmd->argv = NULL;
	new_cmd->pid = -1;
	new_cmd->redirection = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
