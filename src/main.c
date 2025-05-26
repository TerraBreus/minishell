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

	if (shell_init(&shell) == FAILURE)
		return (quick_clean(&shell), EXIT_FAILURE);
	while (true)
		loop(&shell);
}
