/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:59:38 by masmit            #+#    #+#             */
/*   Updated: 2024/11/01 17:19:29 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// dont check either for zero, otherwise it wont pass paco
// memset dont work the same as bzero
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;

	arr = malloc(nmemb * size);
	if (arr == NULL)
		return (arr);
	ft_bzero(arr, size * nmemb);
	return (arr);
}

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	size_t	calloc_size;
// 	void	*arr;

// 	if (nmemb == 0)
// 		return (0);
// 	calloc_size = nmemb * size;
// 	arr = malloc(sizeof(void) * calloc_size);
// 	if (arr != NULL)
// 		ft_memset(arr, 0, calloc_size);
// 	return (arr);
// }
