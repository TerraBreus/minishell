/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/18 18:11:23 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(t_shell *shell, char *str, size_t *i)
{
	size_t	start;
	char	*var_name;
	char	*value;

	start = *i + 1;
	if (str[start] == '?')
	{
		*i = start + 1;
		return (ft_itoa(shell->last_errno));
	}
	if (!is_filename_char(str[start]))
		return (*i = start, ft_strdup("$"));
	while (is_filename_char(str[start]))
		start++;
	var_name = ft_substr(str, *i + 1, start - (*i + 1));
	if (!var_name)
		malloc_fail(shell, "expand var");
	value = my_getenv(shell, var_name);
	free(var_name);
	*i = start;
	if (value)
		return (value);
	return (ft_strdup(""));
}

static char	*handle_expansion(
	t_shell *shell, char *str, size_t *i, char *result)
{
	char	*expanded_var;
	char	*temp;

	expanded_var = expand_var(shell, str, i);
	if (!expanded_var)
		malloc_fail(shell, "expand var");
	temp = ft_strjoin(result, expanded_var);
	if (!temp)
		malloc_fail(shell, "handle expansion");
	free(result);
	free(expanded_var);
	return (temp);
}

char	*add_char(t_shell *shell, char *str, size_t *i, char *result)
{
	char	buffer[2];
	char	*temp;

	buffer[0] = str[*i];
	buffer[1] = '\0';
	temp = ft_strjoin(result, buffer);
	if (!result)
		malloc_fail(shell, "add char\n");
	*i += 1;
	free(result);
	return (temp);
}

char	*check_expansion(t_shell *shell, char *str)
{
	size_t	i;
	bool	in_singles;
	bool	in_doubles;
	char	*result;

	i = 0;
	in_singles = false;
	in_doubles = false;
	result = ft_strdup("");
	if (!str)
		return (NULL);
	if (!result)
		malloc_fail(shell, "check expansion");
	while (str[i])
	{
		update_bools(str[i], &in_singles, &in_doubles);
		if (str[i] == '$' && !in_singles)
			result = handle_expansion(shell, str, &i, result);
		else
			result = add_char(shell, str, &i, result);
	}
	return (result);
}
