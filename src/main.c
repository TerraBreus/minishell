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

// parsing, done
// builtin, done export
// 			done env
// 			done pwd
// 			done echo
// 			done unset
// 			done exit
// 			done cd

// TODO: heredoc
// signals, done on interactive mode, missing in exec

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
