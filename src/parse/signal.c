/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/04 15:37:46 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_errno = 130;
		g_signal = 0;
	}
}

void	sigquit(t_shell *shell, char *input)
{
	if (!input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		quick_clean(shell);
		exit(EXIT_SUCCESS);
	}
}

static void	sig_int_handler(int sig)
{
	g_signal = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	signals_init(t_shell *shell)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = sig_int_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) != 0)
	{
		sigaction_fail(shell, errno);
		return (FAILURE);
	}
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) != 0)
	{
		sigaction_fail(shell, errno);
		return (FAILURE);
	}
	return (SUCCESS);
}
