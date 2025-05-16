/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:12 by masmit           ###   ########.fr       */
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

void	cleanup_quotes(t_shell *shell)
{
	char	*new_token;
	size_t	i;

	i = 0;
	new_token = NULL;
	while (shell->tokens[i])
	{
		if (strchr(shell->tokens[i], '"')
			|| strchr(shell->tokens[i], '\''))
		{
			new_token = clean_token(shell, shell->tokens[i]);
			free(shell->tokens[i]);
			shell->tokens[i] = new_token;
		}
		i++;
	}
}
