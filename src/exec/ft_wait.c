/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                           :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:23:23 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/19 16:26:50 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_and_check_errno(void)
{
	while (wait(NULL) != -1)
		;
	if (errno != ECHILD)
	{
		perror("ft_wait: ");
		exit(EXIT_FAILURE);
	}
}

int	ft_wait(t_shell *shell, int last_pid, int *status)
{
	if (last_pid > 0)
	{
		waitpid(last_pid, status, 0);
		wait_and_check_errno();
		if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			shell->last_errno = 130;
		}
		else if (WIFEXITED(*status) != 0)
			shell->last_errno = WEXITSTATUS(*status);
	}
	wait_and_check_errno();
	return (1);
}
