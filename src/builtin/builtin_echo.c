/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by n One             #+#    #+#             */
/*   Updated: 2025/06/16 12:36:21 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	handle_newline(char **arg_array, bool *newline_flag)
{
	size_t	i;
	size_t	j;

	i = 1;
	*newline_flag = false;
	if (!arg_array[i])
		return (1);
	while (arg_array[i] && arg_array[i][0] == '-' && arg_array[i][1] == 'n')
	{
		j = 2;
		while (arg_array[i][j] == 'n')
			j++;
		if (arg_array[i][j] == '\0')
		{
			*newline_flag = true;
			i++;
		}
		else
			break ;
	}
	return (i);
}

// echo in bash can have multiple arguments so imma just print them as an array
int	my_echo(char **arg_array)
{
	bool	newline_flag;
	size_t	i;

	newline_flag = false;
	i = handle_newline(arg_array, &newline_flag);
	while (arg_array[i])
	{
		write(STDOUT_FILENO, arg_array[i], ft_strlen(arg_array[i]));
		if (arg_array[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline_flag == false)
		(write(STDOUT_FILENO, "\n", 1));
	return (0);
}
