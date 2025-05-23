/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   And all the pieces matter...                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Me                                         +#+  +:+       +#+        */
/*       Shoutout to: Terry A. Davis              +#+#+#+#+#+   +#+           */
/*   Created: / 66:77:88 by The Chosen One             #+#    #+#             */
/*   Updated: / 66:77:88 by Me                        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_node(t_shell *shell)
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

static void	add_cmd_back(t_cmd **exec, t_cmd *new_cmd)
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

void	token_to_struct(t_shell *shell, t_cmd **exec)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	if (shell->found_error == true)
		return ;
	while (shell->tokens[i])
	{
		cmd = new_node(shell);
		if (!cmd)
		{
			malloc_fail(shell, "token to struct");
			return ;
		}
		add_args(shell, cmd, shell->tokens, &i);
		add_redir(shell, cmd, shell->tokens, &i);
		add_cmd_back(exec, cmd);
		if (shell->tokens[i] && ft_strncmp(shell->tokens[i], "|", 1) == 0)
			i++;
	}
}
