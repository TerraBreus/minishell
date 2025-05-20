/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   And all the pieces matter...                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Me                                         +#+  +:+       +#+        */
/*       Shoutout to: Terry A. Davis              +#+#+#+#+#+   +#+           */
/*   Created: / 66:77:88 by The Chosen One             #+#    #+#             */
/*   Updated: / 66:77:88 by Me                        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clean_str(
	t_shell *shell, char *str, size_t *i, char *result)
{
	char	quote;

	quote = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != quote)
	{
		result = ft_strjoin_char(result, str[*i]);
		if (!result)
			return (malloc_fail(shell, "clean str"), NULL);
		*i += 1;
	}
	if (str[*i] == quote)
		*i += 1;
	return (result);
}

static char	*join_char(
	t_shell *shell, char *str, size_t *i, char *result)
{
	result = ft_strjoin_char(result, str[*i]);
	if (!result)
		return (malloc_fail(shell, "handle regular char"), NULL);
	*i += 1;
	return (result);
}

static char	*clean_token(t_shell *shell, char *str)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (malloc_fail(shell, "remove all quotes"), NULL);
	while (str[i])
	{
		if (is_quote(str[i]))
			result = clean_str(shell, str, &i, result);
		else
			result = join_char(shell, str, &i, result);
	}
	return (result);
}

char	*cleanup_quotes(t_shell *shell, char *token)
{
	char	*new_token;

	new_token = NULL;
	if (!token)
		return (NULL);
	if (strchr(token, '"')
		|| strchr(token, '\''))
	{
		new_token = clean_token(shell, token);
		free(token);
		return (new_token);
	}
	else
		return (token);
}
