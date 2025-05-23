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

void	malloc_fail(t_shell *shell, char *location)
{
	ft_putstr_fd("malloc failed at: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = ENOMEM;
}

void	syntax_error(t_shell *shell, char *invalid_token)
{
	ft_putstr_fd("error: \
syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(invalid_token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = SYNTAX_ERROR;
}

void	sigaction_fail(t_shell *shell, int error)
{
	ft_putstr_fd("sigaction setup failed", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = error;
}
