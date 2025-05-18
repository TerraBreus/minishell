/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:44 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parsing, done
// signals, done on interactive mode, missing in exec
// builtin, done export
// 			done local vars
// 			done env
// 			done echo
// 			done unset

// TODO: heredoc, cd, pwd, exit

int	main(void)
{
	t_shell	shell;

	if (env_init(&shell) == FAILURE)
		return (cleanup_shell(&shell), EXIT_FAILURE);
	shell.last_errno = 0;
	while (true)
		loop(&shell);
	return (shell.last_errno);
}
