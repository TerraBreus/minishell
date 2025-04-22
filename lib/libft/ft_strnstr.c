/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:01:52 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:12:44 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// checks for presence of needle in haystack.
// if found, returns location of needle.
// o = overlap
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	o;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		o = 0;
		if (haystack[i] == needle[o])
		{
			while (haystack[i + o] == needle[o] && i + o < len)
			{
				if (needle[o + 1] == '\0')
					return ((char *)haystack + i);
				o++;
			}
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char haystack[50] = "123467890";
// 	char needle[50] = "a";
// 	size_t len = 10;
// 	printf("%s\n", ft_strnstr(haystack, needle, len));
// 	//printf("%s\n", strnstr(haystack, needle, len));
// }