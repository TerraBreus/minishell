/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:09:28 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (OUT);
	if (type == TOKEN_APPEND)
		return (APPEND);
	if (type == TOKEN_HEREDOC)
		return (HEREDOC);
	return (NONE);
}

void	append_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*last;

	if (!cmd->redirection)
		cmd->redirection = redir;
	else
	{
		last = cmd->redirection;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

void	copy_argv(char **new_argv, char **old_argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
}
