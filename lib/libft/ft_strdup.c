/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:09:24 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:55:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy string and return pointer to location of new string
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s2;

	len = 0;
	len = ft_strlen(s);
	s2 = (char *)malloc((len +1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s, len + 1);
	return (s2);
}

/*int main (void)
{
	const char s1[50] = "In this second part, you must";
	printf("%s\n", ft_strdup(s1));
}*/