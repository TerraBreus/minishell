/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:27 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redir_type(char *token)
{
	if (ft_strncmp(token, "<", 1) == 0)
		return (IN);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUT);
	if (ft_strncmp(token, "<<", 2) == 0)
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
	new_node->filename_path = cleanup_quotes(shell, ft_strdup(next_token));
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

	while (tokens[*i] && *tokens[*i] != '|')
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
	while (tokens[*i] && *tokens[*i] != '|'
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
		cmd->argv[j] = cleanup_quotes(shell, ft_strdup(tokens[start + j]));
		if (!cmd->argv[j])
			malloc_fail(shell, "add args");
		j++;
	}
	cmd->argv[j] = NULL;
}
