/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:50:00 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:54:46 by masmit           ###   ########.fr       */
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
