/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:06 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clean_token(char *str)
{
	char	result[4096];
	size_t	i;
	size_t	len;
	char	quote;

	len = 0;
	ft_memset(result, '\0', 4096);
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				result[len++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			result[len++] = str[i++];
	}
	return (ft_strdup(result));
}

char	*cleanup_quotes(t_shell *shell, char *token)
{
	char	*new_token;

	(void)shell;
	new_token = NULL;
	if (!token)
		return (NULL);
	if (!strchr(token, '"')
		&& !strchr(token, '\''))
	{
		token = ft_strdup(token);
		if (!token)
			return (malloc_fail(shell, "cleanup quotes"), NULL);
		return (token);
	}
	new_token = clean_token(token);
	if (!new_token)
		return (malloc_fail(shell, "cleanup quotes"), NULL);
	return (new_token);
}
