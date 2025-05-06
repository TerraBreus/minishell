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

static void	add_argument(t_cmd *cmd, char *token)
{
	int		argc;
	char	**new_argv;

	argc = 0;
	if (cmd->argv)
		while (cmd->argv[argc])
			argc++;
	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return ;
	if (cmd->argv)
	{
		copy_argv(new_argv, cmd->argv, argc);
		free(cmd->argv);
	}
	new_argv[argc] = ft_strdup(token);
	if (!new_argv[argc])
	{
		free(new_argv);
		return ;
	}
	new_argv[argc + 1] = NULL;
	cmd->argv = new_argv;
}

static int	handle_redirection(t_list **token_list, t_cmd *cmd)
{
	t_redir			*redir;
	t_token_data	*file_token;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir || !(*token_list)->next)
		return (1);
	redir->type = get_redir_type((
				(t_token_data *)(*token_list)->content)->type);
	*token_list = (*token_list)->next;
	file_token = (t_token_data *)(*token_list)->content;
	if (file_token->type != TOKEN_WORD
		&& file_token->type != TOKEN_WORD_WITH_PATH)
		return (1);
	redir->filename_path = ft_strdup(file_token->token);
	redir->heredoc_fd = -1;
	redir->next = NULL;
	append_redir(cmd, redir);
	return (0);
}

static int	handle_token(t_list **token_list, t_cmd *cmd)
{
	t_token_data	*data;

	data = (t_token_data *)(*token_list)->content;
	if (data->type == TOKEN_PIPE)
	{
		*token_list = (*token_list)->next;
		return (1);
	}
	else if (data->type == TOKEN_REDIRECT_IN
		|| data->type == TOKEN_REDIRECT_OUT
		|| data->type == TOKEN_APPEND
		|| data->type == TOKEN_HEREDOC)
		return (handle_redirection(token_list, cmd));
	else if (data->type == TOKEN_WORD
		|| data->type == TOKEN_WORD_WITH_PATH)
		add_argument(cmd, data->token);
	return (0);
}

t_cmd	*cmd_struct(t_list *token_list)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_tail;
	t_cmd	*cmd;

	cmd_head = NULL;
	cmd_tail = NULL;
	while (token_list)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		if (!cmd_head)
			cmd_head = cmd;
		else
			cmd_tail->next = cmd;
		cmd_tail = cmd;
		while (token_list
			&& !handle_token(&token_list, cmd))
			token_list = token_list->next;
	}
	return (cmd_head);
}
