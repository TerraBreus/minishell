/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:24:55 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/18 18:26:46 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static int	setup_heredoc(t_shell *shell, char *delim)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	if (pipe(pfd) == -1)
		exit(1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		run_heredoc(shell, pfd, delim);
	close(pfd[1]);
	ft_wait(shell, pid, &status);
	store_heredoc(pfd[0]);
	signals_init(shell);
	if (WIFSIGNALED(status)
		&& WTERMSIG(status) == SIGINT)
		return (shell->last_errno = 130, -1);
	return (0);
}

int	heredoc(t_shell *shell, char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], "<<", 3) == 0)
		{
			if (setup_heredoc(shell, arr[i + 1]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
