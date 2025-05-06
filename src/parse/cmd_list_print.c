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

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("  argv[%d] = [%s]\n", i, argv[i]);
		i++;
	}
}

void	print_redirections(t_redir *redir)
{
	const char	*type_str;

	while (redir)
	{
		type_str = "UNKNOWN";
		if (redir->type == IN)
			type_str = "IN (<)";
		else if (redir->type == OUT)
			type_str = "OUT (>)";
		else if (redir->type == APPEND)
			type_str = "APPEND (>>)";
		else if (redir->type == HEREDOC)
			type_str = "HEREDOC (<<)";
		printf("\t%s, filename = [%s]\n", type_str, redir->filename_path);
		redir = redir->next;
	}
}

void	print_cmd_list(t_cmd *cmd_list)
{
	int			cmd_index;
	t_redir		*redir;

	cmd_index = 0;
	while (cmd_list)
	{
		printf("Command #%d:\n", cmd_index++);
		if (cmd_list->argv)
			print_argv(cmd_list->argv);
		else
			printf("  argv = NULL\n");
		redir = cmd_list->redirection;
		if (!redir)
			printf("  redirection = not found\n");
		else
		{
			printf("  redirections:\n");
			print_redirections(redir);
		}
		printf("\n");
		cmd_list = cmd_list->next;
	}
}
