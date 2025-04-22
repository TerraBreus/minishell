/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printBasics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:02:57 by masmit            #+#    #+#             */
/*   Updated: 2024/11/09 16:20:39 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_print_string(va_list arguments)
{
	int		i;
	char	*str;

	i = 0;
	str = va_arg(arguments, char *);
	if (str == NULL)
		return (write (1, "(null)", 6));
	while (str[i] != '\0')
	{
		ft_print_char(str[i]);
		i++;
	}
	return (i);
}

int	ft_print_normalstring(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_print_char(str[i]);
		i++;
	}
	return (i);
}
