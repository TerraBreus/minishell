/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:02:06 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_init(t_shell *shell, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	shell->env_copy = malloc(sizeof(char *) * (i + 1));
	if (!shell->env_copy)
	{
		malloc_fail(shell, "env_copy");
		return ;
	}
	i = 0;
	while (env[i])
	{
		shell->env_copy[i] = ft_strdup(env[i]);
		if (!shell->env_copy[i])
		{
			malloc_fail(shell, "env_copy[i]");
			return ;
		}
		i++;
	}
	shell->env_copy[i] = NULL;
}

void	local_init(t_shell *shell)
{
	shell->local_vars = malloc(sizeof(char *));
	if (!shell->local_vars)
		malloc_fail(shell, "vars_init");
	shell->local_vars[0] = NULL;
}
