/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:43:54 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 16:31:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// file descriptor is used for handeling the space between user and kernel
// location in table, takes first given location available
// 0 = error, 1 = file, 2 = dont write
// to identify file/socket resources
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
