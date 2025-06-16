/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:23:23 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/07 14:56:21 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait(t_shell *shell, int last_pid, int *status)
{
	if (last_pid > 0)
	{
		waitpid(last_pid, status, 0);
		while (wait(NULL) != -1)
			;
		if (errno != ECHILD)
		{
			perror("ft_wait: ");
			exit(EXIT_FAILURE);
		}
		if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		{	
			ft_putchar_fd('\n', STDOUT_FILENO);
			shell->last_errno = 130;
		}
		else if (WIFEXITED(*status) != 0)
			shell->last_errno = WEXITSTATUS(*status);
	}
	while (wait(NULL) != -1)
		;
	if (errno != ECHILD)
	{
		perror("ft_wait: ");
		exit(EXIT_FAILURE);
	}
	return (1);
}
