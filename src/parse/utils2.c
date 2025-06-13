/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:06 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous(t_shell *shell)
{
	write(2, "minishell: ambiguous redirect\n", 31);
	shell->found_error = true;
	shell->last_errno = 1;
}

t_type	redir_type(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (IN);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (APPEND);
	if (ft_strncmp(token, ">", 2) == 0)
		return (OUT);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (HEREDOC);
	return (NONE);
}

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
		free_arr(current->argv);
		clean_redir(&current->redirection);
		free(current);
		current = next;
	}
	*exec = NULL;
}
