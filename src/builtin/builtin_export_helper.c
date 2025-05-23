/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 16:12:38 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_var(t_shell *shell, char *str)
{
	size_t	i;

	i = 0;
	while (shell->env[i])
		i++;
	shell->env = ft_realloc(shell->env,
			sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	if (!shell->env)
		malloc_fail(shell, "add var");
	shell->env[i] = ft_strdup(str);
	if (!shell->env[i])
		malloc_fail(shell, "add var");
	shell->env[i + 1] = NULL;
}

static void	update_var(t_shell *shell, size_t i, char *str)
{
	free(shell->env[i]);
	shell->env[i] = ft_strdup(str);
	if (!shell->env[i])
		malloc_fail(shell, "update var");
}

void	add_to_env(t_shell *shell, char *str)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strchr(str, '=') - str;
	i = find_index(shell->env, str, len);
	if (i != -1)
		update_var(shell, i, str);
	else
		add_var(shell, str);
}
