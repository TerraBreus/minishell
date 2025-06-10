/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/10 14:12:26 by masmit           ###   ########.fr       */
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

t_redir_type	get_redir_type(char *token)
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

static void	create_redir(
	t_shell *shell, t_cmd *cmd, char *token, char *next_token)
{
	t_redir	*new_node;
	t_redir	*temp;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		malloc_fail(shell, "create redir");
	new_node->type = get_redir_type(token);
	new_node->filename_quotes = false;
	if (next_token[0] == '\'' || next_token[0] == '"')
		new_node->filename_quotes = true;
	new_node->filename_path = cleanup_quotes(shell, next_token);
	new_node->heredoc_fd = -1;
	new_node->next = NULL;
	if (!cmd->redirection)
	{
		cmd->redirection = new_node;
		return ;
	}
	temp = cmd->redirection;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	add_arg_to_cmd(t_shell *shell, t_cmd *cmd, char *token)
{
	char	*arg;
	char	**new_argv;
	size_t	count;
	size_t	j;

	j = 0;
	count = 0;
	arg = cleanup_quotes(shell, token);
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		malloc_fail(shell, "add_arg_to_cmd");
	while (j < count)
	{
		new_argv[j] = cmd->argv[j];
		j++;
	}
	new_argv[count] = arg;
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	token_to_struct(t_shell *shell, t_cmd **exec)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	while (shell->tokens[i])
	{
		cmd = new_node(shell);
		while (shell->tokens[i] && *shell->tokens[i] != '|')
		{
			if (get_redir_type(shell->tokens[i]) != NONE)
			{
				if (!shell->tokens[i + 1])
					break ;
				create_redir(
					shell, cmd, shell->tokens[i], shell->tokens[i + 1]);
				i += 2;
			}
			else
				add_arg_to_cmd(shell, cmd, shell->tokens[i++]);
		}
		add_cmd_back(exec, cmd);
		if (shell->tokens[i] && *shell->tokens[i] == '|')
			i++;
	}
}
