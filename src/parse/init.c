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

extern char	**environ;

static int	pwd_init(t_shell *shell)
{
	shell->old_pwd = malloc(PATH_MAX);
	if (!shell->old_pwd)
		return (malloc_fail(shell, "env init"), FAILURE);
	getcwd(shell->old_pwd, PATH_MAX);
	return (SUCCESS);
}

int	env_init(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (environ[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	shell->exp_copy = malloc(sizeof(char *) * (i + 1));
	if (!shell->env || !shell->exp_copy)
		return (malloc_fail(shell, "env init"), FAILURE);
	i = 0;
	while (environ[i])
	{
		shell->env[i] = ft_strdup(environ[i]);
		shell->exp_copy[i] = ft_strdup(environ[i]);
		if (!shell->env[i] || !shell->exp_copy[i])
			return (malloc_fail(shell, "env[i]"), FAILURE);
		i++;
	}
	shell->env[i] = NULL;
	shell->exp_copy[i] = NULL;
	bubble_sort(shell->exp_copy, i);
	return (SUCCESS);
}

int	shell_init(t_shell *shell)
{
	if (!isatty(1) || !isatty(0))
		return (FAILURE);
	if (env_init(shell) == FAILURE)
		return (FAILURE);
	if (pwd_init(shell) == FAILURE)
		return (FAILURE);
	if (signals_init(shell) == FAILURE)
		return (FAILURE);
	shell->last_errno = 0;
	return (SUCCESS);
}
