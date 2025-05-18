/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo in bash can have multiple arguments so imma just print them as an array
void	my_echo(char **arg_array)
{
	bool	newline_flag;
	size_t	i;

	i = 1;
	newline_flag = false;
	if (!arg_array || !arg_array[i])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	while (arg_array[i]
		&& ft_strncmp(arg_array[i], "-n", 2) == 0)
	{
		newline_flag = true;
		i++;
	}
	while (arg_array[i])
	{
		write(STDOUT_FILENO, arg_array[i], ft_strlen(arg_array[i]));
		if (arg_array[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline_flag == false)
		(write(STDOUT_FILENO, "\n", 1));
}
