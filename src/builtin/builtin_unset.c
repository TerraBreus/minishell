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

void	remove_arg(char **env, size_t *delete_pos)
{
	size_t	i;

	i = *delete_pos;
	free(env[*delete_pos]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	*delete_pos = i;
}

static int	var_match(char *env_item, char *to_remove)
{
	size_t	env_len;
	size_t	remove_len;

	env_len = 0;
	while (env_item[env_len] != '=')
		env_len++;
	remove_len = ft_strlen(to_remove);
	if (env_len != remove_len)
		return (FAILURE);
	if (ft_strncmp(env_item, to_remove, env_len) == 0)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	my_unset(t_shell *shell, char **arg_list)
{
	size_t	i;
	size_t	j;

	j = 1;
	while (arg_list[j] != NULL)
	{
		i = 0;
		while (shell->env[i] != NULL)
		{
			if (var_match(shell->env[i], arg_list[j]) == SUCCESS)
				remove_arg(shell->env, &i);
			else
				i++;
		}
		j++;
	}
	return (0);
}
