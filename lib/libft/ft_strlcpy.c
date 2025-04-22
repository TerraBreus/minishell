/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:13:51 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:02:01 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// append (src to dest), into location of src. limited by size
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// int main(void)
// {
// 	char src[50] = "the cake is a lie !\0I'm hidden lol\r\n";
// 	char dst[50] = "the cake is a lie !\0I'm hidden lol\r\n";
// 	printf("%zu\n", ft_strlcpy(src, dst, 0));
// 	//printf("%zu\n", strlcpy(src, dst, 0));
// }