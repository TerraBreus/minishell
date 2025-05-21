/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:13:56 by masmit            #+#    #+#             */
/*   Updated: 2024/11/01 18:16:38 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *pointer, size_t old_size, size_t new_size)
{
	void	*new_pointer;

	if (new_size == 0)
	{
		free(pointer);
		return (NULL);
	}
	if (pointer == NULL)
		return (malloc(new_size));
	new_pointer = malloc(new_size);
	if (!new_pointer)
		return (NULL);
	if (old_size < new_size)
	{
		ft_memcpy(new_pointer, pointer, old_size);
		ft_memset((char *)new_pointer + old_size, 0, new_size - old_size);
	}
	else
		ft_memcpy(new_pointer, pointer, new_size);
	free(pointer);
	return (new_pointer);
}
