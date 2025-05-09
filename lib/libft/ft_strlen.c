/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:39:23 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 15:02:10 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// c'mon man
size_t	ft_strlen(const char *s1)
{
	size_t	a;

	a = 0;
	while (s1[a] != '\0')
		a++;
	return (a);
}

/*int main(void)
{
    char *s1 = "tree.";
    printf("%zu\n", ft_strlen(s1));
    printf("%zu\n", strlen(s1));
}*/