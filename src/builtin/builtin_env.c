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

void	my_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env_copy[i])
	{
		write(STDOUT_FILENO, shell->env_copy[i], ft_strlen(shell->env_copy[i]));
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

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
			while (shell->env_copy[env_items][i]
					&& shell->env_copy[env_items][i] != '=')
				i++;
			return (ft_substr(shell->env_copy[env_items], i + 1,
					ft_strlen(shell->env_copy[env_items]) - i));
		}
		env_items++;
	}
	return (NULL);
}
