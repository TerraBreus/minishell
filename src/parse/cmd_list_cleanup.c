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

static void	cleanup_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->filename_path)
			free(tmp->filename_path);
		free(tmp);
	}
}

static void	cleanup_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	cleanup_cmd_list(t_cmd *cmd_head)
{
	t_cmd	*tmp;

	while (cmd_head)
	{
		tmp = cmd_head;
		cmd_head = cmd_head->next;
		cleanup_argv(tmp->argv);
		cleanup_redirections(tmp->redirection);
		free(tmp);
	}
}
