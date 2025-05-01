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

char	*my_getenv(t_custom_env *my_env, char *variable)
{
	size_t			env_items;
	size_t			variable_len;
	size_t			i;

	i = 0;
	if (!variable)
		return (NULL);
	env_items = 0;
	variable_len = ft_strlen(variable);
	while (my_env->env_copy[env_items])
	{
		if (ft_strncmp(my_env->env_copy[env_items],
				variable, variable_len) == 0)
		{
			while (my_env->env_copy[env_items][i] != '=')
				i++;
			return (ft_substr(my_env->env_copy[env_items], i + 1,
					ft_strlen(my_env->env_copy[env_items]) - i));
		}
		env_items++;
	}
	return (NULL);
}

void	my_unset(t_custom_env *my_env, char *variable)
{
	size_t			env_items;
	size_t			leftover;

	env_items = 0;
	while (my_env->env_copy[env_items])
	{
		if (ft_strncmp(my_env->env_copy[env_items],
				variable, ft_strlen(variable)) == 0
			&& my_env->env_copy[env_items][ft_strlen(variable)] == '=')
		{
			free(my_env->env_copy[env_items]);
			leftover = env_items;
			while (my_env->env_copy[leftover])
			{
				my_env->env_copy[leftover] = my_env->env_copy[leftover + 1];
				leftover++;
			}
			return ;
		}
		env_items++;
	}
}

void	add_new_var(t_custom_env *my_env, char *new_var_and_value)
{
	size_t	env_items;

	env_items = 0;
	while (my_env->env_copy[env_items])
		env_items++;
	my_env = ft_realloc(my_env,
			sizeof(char *) * env_items,
			sizeof(char *) * env_items + 2);
	if (!my_env)
		return (malloc_fail("malloc failed for adding env parameter", my_env));
	my_env->env_copy[env_items] = new_var_and_value;
	my_env->env_copy[env_items + 1] = NULL;
}

// ugly -1 env items i know but otherwise id have to fight norminette
void	my_export(t_custom_env *my_env, char *new_var, char *value)
{
	size_t	new_var_len;
	size_t	env_items;
	char	*new_var_and_value;

	env_items = -1;
	new_var_len = ft_strlen(new_var);
	new_var_and_value = ft_strjoin(new_var, "=");
	new_var_and_value = ft_strjoin(new_var_and_value, value);
	if (!new_var_and_value)
		return (malloc_fail("when joining strings", my_env));
	while (my_env->env_copy[++env_items])
	{
		if (ft_strncmp(my_env->env_copy[env_items], new_var, new_var_len) == 0
			&& my_env->env_copy[env_items][new_var_len] == '=')
		{
			free(my_env->env_copy[env_items]);
			my_env->env_copy[env_items] = malloc(
					new_var_len + ft_strlen(value) + 2);
			if (!my_env->env_copy[env_items])
				return (malloc_fail("for replacing env parameter", my_env));
			my_env->env_copy[env_items] = new_var_and_value;
			return ;
		}
	}
	add_new_var(my_env, new_var_and_value);
}
