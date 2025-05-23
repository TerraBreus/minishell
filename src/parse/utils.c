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

void	skip_space(char *input, size_t *i)
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
