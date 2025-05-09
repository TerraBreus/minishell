/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:30:48 by masmit            #+#    #+#             */
/*   Updated: 2024/11/01 17:12:54 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// used strchr to remove (character in set) overlapping (characters from s1)
//t_s is trimmed string.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*t_s;

	end = ft_strlen(s1);
	start = 0;
	if (!s1 && !set)
		return (NULL);
	while (s1[start] && ft_strrchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end -1]) && end > start)
		end--;
	t_s = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!t_s)
		return (0);
	ft_strlcpy(t_s, &s1[start], end - start + 1);
	return (t_s);
}

// int main(void)
// {
// 	char s1[50] = "";
// 	char set[50] = "";
// 	printf("%s\n", ft_strtrim(s1, set));
// }