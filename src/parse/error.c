/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:14:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_fail(t_shell *shell, char *location)
{
	ft_putstr_fd("malloc failed at: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->found_error = TRUE;
	shell->last_errno = ENOMEM;
}

void	syntax_error(t_shell *shell, char *invalid_token)
{
	ft_putstr_fd("error: \
syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(invalid_token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->found_error = TRUE;
	shell->last_errno = SYNTAX_ERROR;
}
