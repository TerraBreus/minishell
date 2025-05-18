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
	while (is_filename_char(str[start]))
		start++;
	var_name = ft_substr(str, *i + 1, start - (*i + 1));
	if (!var_name)
		return (malloc_fail(shell, "expand var"), NULL);
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
	temp = ft_strjoin(result, expanded_var);
	if (!temp)
		return (malloc_fail(shell, "handle expansion"), NULL);
	free(result);
	free(expanded_var);
	return (temp);
}

static char	*check_expansion(t_shell *shell, char *str)
{
	size_t	i;
	bool	in_singles;
	bool	in_doubles;
	char	*result;

	i = 0;
	in_singles = false;
	in_doubles = false;
	result = ft_strdup("");
	if (!result)
		return (malloc_fail(shell, "check expansion"), NULL);
	while (str[i])
	{
		update_bools(str[i], &in_singles, &in_doubles);
		if (str[i] == '$' && !in_singles)
			result = handle_expansion(shell, str, &i, result);
		else
		{
			result = ft_strjoin_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

void	expand_tokens(t_shell *shell)
{
	size_t	i;
	char	*new_token;

	i = 0;
	if (shell->found_error == true)
		return ;
	while (shell->tokens[i])
	{
		if (has_path(shell->tokens[i]) == true)
		{
			new_token = check_expansion(shell, shell->tokens[i]);
			free(shell->tokens[i]);
			shell->tokens[i] = new_token;
		}
		i++;
	}
}
