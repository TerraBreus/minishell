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

extern char	**environ;

void	env_init(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (environ[i])
		i++;
	shell->env_copy = malloc(sizeof(char *) * (i + 1));
	if (!shell->env_copy)
		malloc_fail(shell, "env_copy");
	i = 0;
	while (environ[i])
	{
		shell->env_copy[i] = ft_strdup(environ[i]);
		if (!shell->env_copy[i])
			malloc_fail(shell, "env_copy[i]");
		i++;
	}
	shell->env_copy[i] = NULL;
}
