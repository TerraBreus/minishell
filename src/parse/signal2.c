/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:41:38 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_hd(int pfd[2], char *delim)
{
	write(2, EOF_ERROR, ft_strlen(EOF_ERROR));
	write(2, delim, ft_strlen(delim));
	write(2, "'\n", 2);
	close(pfd[1]);
	exit(0);
}

bool	sigint_hd(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(2, "^C\n", 4);
		return (true);
	}
	return (false);
}

void	sigint_parent(t_shell *shell_data, pid_t pid)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signals_init(shell_data);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell_data->last_errno = 128 + sig;
		if (sig == SIGINT)
			write(2, "\n", 1);
	}
}
