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
	size_t			env_items;

	env_items = 0;
	my_env = malloc(sizeof(t_custom_env));
	if (!my_env)
		return (NULL);
	while (env[env_items])
		env_items++;
	my_env->env_copy = malloc(sizeof(char *) * (env_items + 1));
	if (!my_env->env_copy)
		return (free(my_env), NULL);
	env_items = 0;
	while (env[env_items])
	{
		my_env->env_copy[env_items] = ft_strdup(env[env_items]);
		if (!my_env->env_copy[env_items])
			return (cleanup_env(my_env), NULL);
		env_items++;
	}
	my_env->env_copy[env_items] = NULL;
	return (my_env);
}

void	cleanup_env(t_custom_env *my_env)
{
	size_t	env_items;

	env_items = 0;
	while (my_env->env_copy[env_items])
	{
		free(my_env->env_copy[env_items]);
		env_items++;
	}
	free(my_env->env_copy);
	free(my_env);
	return ;
}
