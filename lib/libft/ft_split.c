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

// if any word allocation fails
static char	**free_split(char **s, int i)
{
	while (i > 0)
	{
		i--;
		free(s[i]);
	}
	free(s);
	return (NULL);
}

// allocate the string in between intervals to "word location" in list
static char	**split_words(const char *s, char c, char **s_list, int w_count)
{
	int	i;
	int	word;
	int	w_len;

	i = 0;
	word = 0;
	w_len = 0;
	while (word < w_count)
	{
		w_len = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			w_len++;
		}
		s_list[word] = ft_substr(s, i - w_len, w_len);
		if (s_list[word] == NULL)
			return (free_split(s_list, word));
		word++;
	}
	s_list[word] = NULL;
	return (s_list);
}

// count interval of c in string and return the w count
static int	count_words(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (words);
}

// just call bigger functions
char	**ft_split(char const *s, char c)
{
	char	**s_list;
	int		w_count;

	if (!s)
		return (NULL);
	w_count = count_words(s, c);
	s_list = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (s_list == NULL)
		return (NULL);
	s_list = split_words(s, c, s_list, w_count);
	return (s_list);
}

// memleak cuz not freeing in main.
// int	main(void)
// {
// 	int i = 0;
// 	char s[] = "hello you big beautiful bastard let me come and hold you\n";
// 	char **s_list = ft_split(s, ' ');
// 	while (s_list[i] != NULL)
// 	{
// 		printf("%s\n", s_list[i]);
// 		i++;
// 	}
// 	return (0);
// }