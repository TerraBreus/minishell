/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:05:23 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:12:03 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// appends src to dest, if size allows it.
// if size is to short, returns (src len + size)
// i think a return value of (dest + src) would be more convenient
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	k = 0;
	if (size == 0)
		return (j);
	if (i > size)
		return (j + size);
	while ((i + k) < size -1 && k != j)
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (i + j);
}
// int main(void)
// {
// 	char dst[50] = "12345";
// 	char src[50] = "678";
// 	printf("lenght should be = %zu\n",  ft_strlcat(dst, src, 8));
// }