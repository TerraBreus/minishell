/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:34:38 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:03:55 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// concatenated 1 char to a string, and frees the input
// return result should still be freed
char	*ft_strjoin_char(char *s, char c)
{
	char	buffer[2];
	char	*temp;

	buffer[0] = c;
	buffer[1] = '\0';
	temp = ft_strdup(buffer);
	if (!temp)
		return (free(s), NULL);
	return (ft_strjoin_and_free(s, temp));
}
