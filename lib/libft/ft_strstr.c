/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strstr.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/04/30 15:18:26 by zivanov        #+#    #+#                */
/*   Updated: 2025/04/30 15:29:29 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Yeah yeah I know. I am not Martijn.
** But the original strnstr function is simply put very stupid.
** I don't want to keep track how big my haystack is.
** I simply want to know whether there is a needle in my haystack or not.
** And I will presume a string is correctly null terminated.
** So I will add this function almost exactly the same as ft_strnstr.c
**
** NB: Yes, you must null terminate your
** strings to not send this function to the infinity dimension
*/

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	o;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		o = 0;
		if (haystack[i] == needle[o])
		{
			while (haystack[i + o] == needle[o])
			{
				if (needle[o + 1] == '\0')
					return ((char *)haystack + i);
				o++;
			}
		}
		i++;
	}
	return (NULL);
}
