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

void	remove_arg(char **env_copy, size_t *delete_pos)
{
	size_t	i;

	i = *delete_pos;
	free(env_copy[*delete_pos]);
	while (env_copy[i + 1])
	{
		env_copy[i] = env_copy[i + 1];
		i++;
	}
	env_copy[i] = NULL;
}

void	my_unset(t_shell *shell, char **arg_list)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!arg_list)
		return ;
	while (arg_list[j] != NULL)
	{
		i = 0;
		while (shell->env_copy[i] != NULL)
		{
			if (ft_strncmp(
					shell->env_copy[i], arg_list[j],
					ft_strlen(arg_list[j]) == 0)
				&& shell->env_copy[i][ft_strlen(arg_list[j])] == '=')
				remove_arg(shell->env_copy, &i);
			else
				i++;
		}
		j++;
	}
}
