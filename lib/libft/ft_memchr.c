/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:16:28 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:27:50 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// scan memory for first instance of c
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	while (n--)
	{
		if (*ptr == (const unsigned char)c)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
/*int main(void)
{
	const char s1[50] = "hehfehjbfe";
	const char s2[50] = "hehfehjbfe";
	printf("%s\n", (char *)ft_memchr(s1, 'a', 10));
	printf("%s\n", (char *)memchr(s2, 'a', 10));
}*/