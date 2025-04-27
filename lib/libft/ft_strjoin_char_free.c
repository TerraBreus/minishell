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

// concatenated 1 char to a string, and frees the input
// return result should still be freed
char	*strjoin_char_and_free(char *s, char c)
{
	char	buffer[2];
	char	*temp;

	buffer[0] = c;
	buffer[1] = '\0';
	temp = ft_strdup(buffer);
	if (!temp)
		return (free(s), NULL);
	return (strjoin_and_free(s, temp));
}
