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

void	sigint(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_errno = 130;
		g_signal = 0;
		shell->found_error = true;
	}
}

void	sigquit(char *input)
{
	if (!input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

static void	sig_int_handler(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	rl_redisplay();
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(t_shell *shell)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = sig_int_handler;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) != 0)
	{
		sigaction_fail(shell, errno);
		return ;
	}
	sa_int.sa_flags = SA_RESTART;
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) != 0)
	{
		sigaction_fail(shell, errno);
		return ;
	}
}
