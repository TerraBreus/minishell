/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:43:56 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
