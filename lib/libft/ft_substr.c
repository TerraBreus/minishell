/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:45:14 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:12:55 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// takes part of original string, copies intro new string for len.
// and returns pointer to new string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	s_len;

	i = start;
	j = 0;
	s_len = ft_strlen(s);
	if (!s || start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < s_len && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
// int main(void)
// {
// 	const char s[50] = "In this second part, you must develop";
// 	int start = 8;
// 	size_t len = 600;
// 	printf("%s\n", ft_substr(s, start, len));
// }