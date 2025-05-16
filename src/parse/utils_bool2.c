/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char c)
{
	if (!c)
		return (false);
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

void	just_print(char **temp_arr)
{
	size_t	i;

	i = 0;
	while (temp_arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(temp_arr[i], STDOUT_FILENO);
		free(temp_arr[i]);
		i++;
	}
}
