/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:40:51 by masmit            #+#    #+#             */
/*   Updated: 2024/11/09 20:08:37 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	whats_the_argument(va_list arguments, const char format)
{
	int	print_lenght;

	print_lenght = 0;
	if (format == 'c')
		print_lenght += ft_print_char(va_arg(arguments, int));
	else if (format == 's')
		print_lenght += ft_print_string(arguments);
	else if (format == 'd' || format == 'i')
		print_lenght += ft_print_integer(va_arg(arguments, int));
	else if (format == 'u')
		print_lenght += ft_print_unsigned(va_arg(arguments, unsigned int));
	else if (format == 'x' || format == 'X')
		print_lenght += ft_print_hex(va_arg(arguments, int), format);
	else if (format == 'p')
		print_lenght += ft_print_pointer(va_arg(arguments, uintptr_t));
	else if (format == '%')
		print_lenght += ft_print_char('%');
	return (print_lenght);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int		i;
	int		print_length;

	va_start(arguments, format);
	i = 0;
	print_length = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			print_length += whats_the_argument(arguments, format[i]);
		}
		else
			print_length += ft_print_char(format[i]);
		i++;
	}
	va_end(arguments);
	return (print_length);
}
