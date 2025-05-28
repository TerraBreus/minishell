/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:30 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("  Redirection: ");
		if (redir->type == IN)
			printf("INPUT (<) ");
		else if (redir->type == OUT)
			printf("OUTPUT (>) ");
		else if (redir->type == APPEND)
			printf("APPEND (>>) ");
		else if (redir->type == HEREDOC)
			printf("HEREDOC (<<) ");
		printf("File: %s", redir->filename_path);
		if (redir->heredoc_fd != -1)
			printf(" (fd: %d)", redir->heredoc_fd);
		printf("\n");
		redir = redir->next;
	}
}

static void	print_command_argv(char **argv)
{
	int	i;

	i = 0;
	printf("  Command: ");
	while (argv[i])
	{
		printf("[%s] ", argv[i]);
		i++;
	}
	printf("\n");
}

void	print_exec(t_cmd *exec)
{
	int	cmd_count;

	cmd_count = 1;
	if (!exec)
	{
		printf("No commands in execution list\n");
		return ;
	}
	while (exec)
	{
		printf("Command #%d:\n", cmd_count++);
		print_command_argv(exec->argv);
		print_redirections(exec->redirection);
		if (exec->pid != -1)
			printf("  PID: %d\n", exec->pid);
		exec = exec->next;
		if (exec)
			printf("|\n|\nV\n");
	}
}
