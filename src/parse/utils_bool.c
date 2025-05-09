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

bool	is_operator(char c)
{
	if (!c)
		return (false);
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_path(char *str, size_t *i)
{
	if (str[*i])
	{
		if (str[*i] == '$'
			&& (str[*i + 1] == '_'
				|| str[*i + 1] == '?'
				|| ft_isalnum(str[*i + 1])))
			return (true);
	}
	return (false);
}

bool	has_path(char *str)
{
	size_t	i;

	i = 0;
	skip_litteral(str, &i);
	while (str[i])
	{
		if (is_path(str, &i))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
