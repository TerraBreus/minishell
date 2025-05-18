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

void	my_pwd(t_shell *shell)
{
	size_t	i;
	size_t	j;

	j = 5;
	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], "HOME=", 5) == 0)
		{
			while (shell->env_copy[i][j] != '\0')
			{
				ft_putchar_fd(shell->env_copy[i][j], STDOUT_FILENO);
				j++;
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
}
