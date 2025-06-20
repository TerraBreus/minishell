/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:19 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_fail(t_shell *shell, char *location)
{
	ft_putstr_fd("malloc failed at: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = ENOMEM;
	quick_clean(shell);
	exit(ENOMEM);
}

void	syntax_error(t_shell *shell, char *invalid_token)
{
	ft_putstr_fd("error: \
syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(invalid_token, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = SYNTAX_ERROR;
}

void	sigaction_fail(t_shell *shell, int error)
{
	ft_putstr_fd("sigaction setup failed", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = error;
}

void	filename_invalid(t_shell *shell, char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = 1;
}

void	subject_error(t_shell *shell, char c)
{
	ft_putstr_fd("error: \
minishell: subject doesnt \
require specified meta character: `", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = 1;
}
