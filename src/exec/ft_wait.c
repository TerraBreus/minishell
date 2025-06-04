/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_wait.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:23:23 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:23:27 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait(int last_pid, int *status)
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
		if (WIFEXITED(*status) != 0)
			return (WEXITSTATUS(*status));
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
