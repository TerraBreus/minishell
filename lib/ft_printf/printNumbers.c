/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printNumbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:04:23 by masmit            #+#    #+#             */
/*   Updated: 2024/11/09 20:08:18 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_num_string(char *str)
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

int	ft_print_integer(long int n)
{
	int		len;

	len = 0;
	len = print_len(n);
	if (n == -2147483648)
	{
		ft_print_normalstring("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		ft_print_char('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_print_integer(n / 10);
		n = n % 10;
	}
	if (n < 10)
		ft_print_char(n + '0');
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	return (ft_print_integer((long) n));
}
