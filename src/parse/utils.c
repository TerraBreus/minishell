/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:41:48 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_blank(char *input, size_t *i)
{
	while (input[*i] == ' '
		|| input[*i] == '\t'
		|| input[*i] == '\n')
		*i += 1;
}

void	skip_litteral(char *str, size_t *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] != '\'')
			*i += 1;
		*i += 1;
	}
}

void	print_tokens(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->tc)
	{
		printf("%s\n", shell->tokens[i]);
		i++;
	}
}

bool	is_quote(char c)
{
	if (!c)
		return (false);
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

void	just_print(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		printf("declare -x %s\n", arr[i]);
		i++;
	}
}
