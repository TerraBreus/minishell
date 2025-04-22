/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:36:18 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:05:49 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compares 2 strings per byte, returns first encounterd difference.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0' ) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
// int main(void)
// {
// 	char *s1 = "abcdefgh";
// 	char *s2 = "abcdwxyz";
// 	printf("%d\n", ft_strncmp(s1, s2, 4));
// 	printf("%d\n", strncmp(s1, s2, 4));
// }