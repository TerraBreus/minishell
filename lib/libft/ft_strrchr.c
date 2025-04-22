/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:38:45 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:08:40 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// returns last found location of c in string, NULL if nothing is found
char	*ft_strrchr(const char *string, int c)
{
	int	len;

	len = 0;
	while (string[len] != '\0')
		len++;
	while (len >= 0)
	{
		if (string[len] == (char)c)
			return ((char *)&string[len]);
		len--;
	}
	return (NULL);
}

// int main(void)
// {
// 	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
// 	printf("%s\n", strrchr(src, '\0'));
// 	printf("%s\n", ft_strrchr(src, '\0'));
// }