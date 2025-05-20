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
