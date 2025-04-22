/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:04:18 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:30:30 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// rewrites from src to dest, accounts for overlap in memory
void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (dest == src)
		return (dest);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dest);
	}
	while (len--)
		*d++ = *s++;
	return (dest);
}

/*int main(void)
{
	char dest[50] = "1234567890";
	char src[50] = "tree.";
	printf("%s\n", (char *)ft_memmove(dest, src, 5));
}*/