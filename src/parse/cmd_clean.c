/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:32 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_redir(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current)
	{
		next = current->next;
		if (current->filename_path)
			free(current->filename_path);
		if (current->heredoc_fd != -1)
			close(current->heredoc_fd);
		free(current);
		current = next;
	}
	*redir = NULL;
}

static void	clean_argv(char ***argv)
{
	int	i;

	if (!*argv)
		return ;
	i = 0;
	while ((*argv)[i])
	{
		free((*argv)[i]);
		i++;
	}
	free(*argv);
	*argv = NULL;
}

void	cleanup_struct(t_cmd **exec)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!exec || !*exec)
		return ;
	current = *exec;
	while (current)
	{
		next = current->next;
		clean_argv(&current->argv);
		clean_redir(&current->redirection);
		free(current);
		current = next;
	}
	*exec = NULL;
}
