/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:12 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redir_type(char *token)
{
	if (strcmp(token, "<") == 0)
		return (IN);
	if (strcmp(token, ">>") == 0)
		return (APPEND);
	if (strcmp(token, ">") == 0)
		return (OUT);
	if (strcmp(token, "<<") == 0)
		return (HEREDOC);
	return (NONE);
}

static t_redir	*create_redir(t_shell *shell, char *token, char *next_token)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (malloc_fail(shell, "create redir"), NULL);
	new_node->type = get_redir_type(token);
	new_node->filename_path = ft_strdup(next_token);
	new_node->heredoc_fd = -1;
	new_node->next = NULL;
	return (new_node);
}

static void	add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*temp;

	if (!cmd->redirection)
	{
		cmd->redirection = redir;
		return ;
	}
	temp = cmd->redirection;
	while (temp->next)
		temp = temp->next;
	temp->next = redir;
}

void	add_redir(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i)
{
	t_redir	*redir;

	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
	{
		if (get_redir_type(tokens[*i]) != NONE)
		{
			if (!tokens[*i + 1])
				break ;
			redir = create_redir(shell, tokens[*i], tokens[*i + 1]);
			if (!redir)
			{
				malloc_fail(shell, "add redir");
				return ;
			}
			add_redir_to_cmd(cmd, redir);
			*i += 2;
		}
		else
			*i += 1;
	}
}

void	add_args(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i)
{
	size_t	argc;
	size_t	j;
	size_t	start;

	argc = 0;
	start = *i;
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0
		&& get_redir_type(tokens[*i]) == NONE)
	{
		argc++;
		*i += 1;
	}
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		malloc_fail(shell, "add args");
	j = 0;
	while (j < argc)
	{
		cmd->argv[j] = ft_strdup(tokens[start + j]);
		if (!cmd->argv[j])
			malloc_fail(shell, "add args");
		j++;
	}
	cmd->argv[j] = NULL;
}
