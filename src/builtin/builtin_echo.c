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

// echo in bash can have multiple arguments so imma just print them as an array
int	my_echo(char **arg_array)
{
	bool	newline_flag;
	size_t	i;

	i = 1;
	newline_flag = false;
	if (!arg_array || !arg_array[i])
		return (write(STDOUT_FILENO, "\n", 1), 0);
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
	return (0);
}
