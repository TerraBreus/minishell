/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bool1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:58 by masmit           ###   ########.fr       */
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
		if (str[*i] != '$')
			return (false);
		if (str[*i] == '$'
			&& (str[*i + 1] == '_'
				|| str[*i + 1] == '?'
				|| ft_isalnum(str[*i + 1])))
			return (true);
	}
	return (false);
}

void	update_bools(
char c, bool *in_singles, bool *in_doubles)
{
	if (c == '\'' && !(*in_doubles))
		*in_singles = !(*in_singles);
	else if (c == '"' && !(*in_singles))
		*in_doubles = !(*in_doubles);
}

bool	has_path(char *str)
{
	size_t	i;
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i])
	{
		update_bools(str[i], &in_single, &in_double);
		if (str[i] == '$' && !in_single)
		{
			if (str[i + 1] == '?' || valid_filename(str[i + 1]))
				return (true);
		}
		i++;
	}
	return (false);
}

bool	is_input_empty(t_shell *shell, char *input)
{
	if (*input == '\0')
	{
		shell->found_error = true;
		return (true);
	}
	return (false);
}
