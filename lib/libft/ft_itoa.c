/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:12:44 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 14:21:41 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lenght of string
size_t	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

// convert number into string
char	*ft_itoa(int n)
{
	long int		new;
	size_t			len;
	char			*string;

	len = 0;
	len = ft_len(n);
	if (n < 0)
		new = -(long int)n;
	else
		new = (long int)n;
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	string[len--] = '\0';
	while (new > 0)
	{
		string[len--] = new % 10 + '0';
		new /= 10;
	}
	if (n == 0)
		string[0] = '0';
	if (n < 0)
		string[0] = '-';
	return (string);
}

// int main(void)
// {
// 	printf("%s\n", ft_itoa(-623));
// 	printf("%s\n", ft_itoa(623));
// 	printf("%s\n", ft_itoa(-0));
// 	printf("%s\n", ft_itoa(+2355674));
// 	return (0);
// }