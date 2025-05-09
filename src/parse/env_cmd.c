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

char	*my_getenv(t_shell *shell, char *var_name)
{
	size_t	var_name_len;
	size_t	env_items;
	size_t	i;

	if (!var_name)
		return (NULL);
	env_items = 0;
	i = 0;
	var_name_len = ft_strlen(var_name);
	while (shell->env_copy[env_items])
	{
		if (ft_strncmp(shell->env_copy[env_items],
				var_name, var_name_len) == 0)
		{
			while (shell->env_copy[env_items][i] != '=')
				i++;
			return (ft_substr(shell->env_copy[env_items], i + 1,
					ft_strlen(shell->env_copy[env_items]) - i));
		}
		env_items++;
	}
	return (NULL);
}
