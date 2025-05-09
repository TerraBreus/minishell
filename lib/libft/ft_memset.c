/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:25:37 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:31:03 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// set memory to constant byte "c"
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n-- > 0)
		*(p++) = (unsigned char)c;
	return (s);
}

/*int main(void)
{
	char s1[50] = "Tree Tree.";
	char s2[50] = "Tree Tree.";
	printf("%s\n", (char*)ft_memset(s1, '-', 6));
	printf("%s\n", (char*)memset(s2, '-', 6));
}*/