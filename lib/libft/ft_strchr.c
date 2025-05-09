/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:39:19 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:11:39 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// locate first instance of "c" in the string
char	*ft_strchr(const char *string, int c)
{
	unsigned char	to_find;

	to_find = (unsigned char)c;
	while (*string != '\0')
	{
		if (*string == to_find)
			return ((char *)string);
		string++;
	}
	if (to_find == '\0')
		return ((char *)string);
	return (0);
}

// int main(void)
// {
// 	char *s = "traeea.";
// 	int c = 'a';
// 	printf("%s\n", ft_strchr(s, c));
// 	printf("%s\n", strchr(s, c));
// }