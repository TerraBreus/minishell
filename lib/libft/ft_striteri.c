/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:13:37 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:56:27 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// iterate over string and apply function to all characters
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}
// char my_func(int i, char s)
// {
// 	return (ft_tolower(s));
// }

// int main(void)
// {
// 	char s[50] = "treetreeTREE.";
// 	printf("result in main = %s\n", ft_striteri(s, f));
// 	return (0);
// }