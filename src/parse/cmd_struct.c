/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/16 12:57:57 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_redir(
	t_shell *shell, t_cmd *cmd, char *token, char *next_token)
{
	t_redir	*new_node;
	t_redir	*temp;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		malloc_fail(shell, "create redir");
	new_node->type = redir_type(token);
	new_node->filename_quotes = false;
	if (next_token != NULL)
	{
		if (next_token[0] == '\'' || next_token[0] == '"')
			new_node->filename_quotes = true;
	}
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

static void	add_arg_to_cmd(t_shell *shell, t_cmd *cmd, char *token)
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

static void	redir_or_arg(t_shell *shell, t_cmd *cmd, char **arr, size_t *i)
{
	while (arr[*i] && arr[*i][0] != '|')
	{
		if (redir_type(arr[*i]) != NONE)
		{
			if (redir_type(arr[*i]) == AMBIGUOUS)
			{
				create_redir(shell, cmd, arr[*i], NULL);
				*i += 1;
				break ;
			}
			if (redir_type(arr[*i]) != HEREDOC)
				create_redir(shell, cmd, arr[*i], arr[*i + 1]);
			*i += 2;
		}
		else
			add_arg_to_cmd(shell, cmd, arr[(*i)++]);
	}
}

void	token_to_struct(t_shell *shell, char **arr, t_cmd **exec)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	while (arr[i] && shell->found_error == false)
	{
		cmd = new_node(shell);
		redir_or_arg(shell, cmd, arr, &i);
		add_cmd_back(exec, cmd);
		if (arr[i] && arr[i][0] == '|')
			i++;
	}
}
