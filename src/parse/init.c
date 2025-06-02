/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:13 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static int	pwd_init(t_shell *shell)
{
	shell->old_pwd = malloc(PATH_MAX);
	if (!shell->old_pwd)
		malloc_fail(shell, "env init");
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
	shell->export = malloc(sizeof(char *) * (i + 1));
	if (!shell->env || !shell->export)
		malloc_fail(shell, "env init");
	i = 0;
	while (environ[i])
	{
		shell->env[i] = ft_strdup(environ[i]);
		shell->export[i] = ft_strdup(environ[i]);
		if (!shell->env[i] || !shell->export[i])
			malloc_fail(shell, "env[i]");
		i++;
	}
	shell->env[i] = NULL;
	shell->export[i] = NULL;
	bubble_sort(shell->export, i);
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
