/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:25:40 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:48 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// write memory from src to dest, for size of n
// doesn't account for overlap
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				counter;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	counter = 0;
	if (!src && !dest)
		return (NULL);
	while (n--)
	{
		d[counter] = s[counter];
		d++;
		s++;
	}
	return (dest);
}
/*int main(void)
{
	char src1[50] = "what a world";
	char dest1[50];
	char src2[50] = "what a world";
	char dest2[50];
	printf("%s\n", (char *)ft_memcpy(dest1, src1, 0));
	printf("%s\n", (char *)memcpy(dest2, src2, 0));
}*/