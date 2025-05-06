/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:52:31 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO, add malloc fail as entry to error list
t_custom_env	*shell_env_init(char **env)
{
	t_custom_env	*my_env;
	size_t			i;

	i = 0;
	my_env = malloc(sizeof(t_custom_env));
	if (!my_env)
		return (NULL);
	while (env[i])
		i++;
	my_env->env_copy = malloc(sizeof(char *) * (i + 1));
	if (!my_env->env_copy)
		return (free(my_env), NULL);
	i = 0;
	while (env[i])
	{
		my_env->env_copy[i] = ft_strdup(env[i]);
		if (!my_env->env_copy[i])
			return (cleanup_env(my_env), NULL);
		i++;
	}
	my_env->env_copy[i] = NULL;
	return (my_env);
}

void	cleanup_env(t_custom_env *my_env)
{
	size_t	i;

	i = 0;
	while (my_env->env_copy[i])
	{
		free(my_env->env_copy[i]);
		i++;
	}
	free(my_env->env_copy);
	free(my_env);
}
