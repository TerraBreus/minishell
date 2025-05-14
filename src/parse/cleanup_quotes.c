/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:14:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes_simple(t_shell *shell, char *str)
{
	char	*result;
	char	*substr_end;
	size_t	i;
	size_t	j;
	char	quote;

	quote = str[0];
	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	result = ft_substr(str, 1, i - 1);
	if (!str[i + 1])
		return (result);
	j = i++;
	while (str[j])
		j++;
	if (j > i)
	{
		substr_end = ft_substr(str, i, j - i);
		result = ft_strjoin_and_free(result, substr_end);
	}
	if (!result)
		malloc_fail(shell, "remove_quotes_simple");
	return (result);
}

void	cleanup_quotes(t_shell *shell)
{
	size_t	i;
	char	*new_token;

	i = 0;
	while (shell->tokens[i])
	{
		if (shell->tokens[i][0] == '\'' || shell->tokens[i][0] == '"')
		{
			new_token = remove_quotes_simple(shell, shell->tokens[i]);
			free(shell->tokens[i]);
			shell->tokens[i] = new_token;
		}
		i++;
	}
}
