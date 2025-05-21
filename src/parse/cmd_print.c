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
