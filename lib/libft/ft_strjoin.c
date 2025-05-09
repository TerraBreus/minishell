/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:34:38 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:57:43 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//n_l is new location.
// joins s1 and s2 in new location, leaves old strings intact
// return new string if succes, NULL if joining fails
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n_l;
	int		lens1;
	int		lens2;
	int		i;

	if (s1 && s2)
	{
		lens1 = ft_strlen(s1);
		lens2 = ft_strlen(s2);
		n_l = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
		if (n_l == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			n_l[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			n_l[lens1] = s2[i];
			lens1++;
		}
		n_l[lens1] = '\0';
		return (n_l);
	}
	return (0);
}

// int main(void)
// {
// 	char s1[50] = "where is my ";
// 	char s2[50] = "malloc ???";
// 	printf("%s\n", ft_strjoin(s1, s2));
// }