/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:04 by masmit            #+#    #+#             */
/*   Updated: 2024/11/09 20:07:19 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>

size_t	print_len(long int n);
int		ft_print_char(char c);
int		ft_print_string(va_list arguments);
int		ft_print_normalstring(char *str);
int		ft_print_integer(long int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, char c);
int		ft_print_pointer(uintptr_t n);
int		whats_the_argument(va_list arguments, const char format);
int		ft_printf(const char *format, ...);

#endif