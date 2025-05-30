/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:21 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(t_shell *shell, char *str, size_t *i)
{
	size_t	start;
	size_t	index;
	char	var_name[4096];
	char	*value;

	index = 0;
	start = *i + 1;
	if (str[start] == '?')
	{
		*i = start + 1;
		return (ft_itoa(shell->last_errno));
	}
	if (!is_filename_char(str[start]))
		return (*i = start, "$");
	while (is_filename_char(str[start]))
		var_name[index++] = str[start++];
	var_name[index] = '\0';
	value = my_getenv(shell, var_name);
	*i = start;
	if (value)
		return (value);
	return ("");
}

void	check_expansion(t_shell *shell, char *str, char *result)
{
	size_t	i;
	bool	in_singles;
	bool	in_doubles;
	char	*buffer;

	i = 0;
	in_singles = false;
	in_doubles = false;
	while (str[i])
	{
		update_bools(str[i], &in_singles, &in_doubles);
		if (str[i] == '$' && !in_singles)
		{
			buffer = expand_var(shell, str, &i);
			ft_strlcat(result, buffer, 4096 - ft_strlen(result));
			free(buffer);
		}
		else
		{
			ft_strlcat(result, &str[i], 4096 - ft_strlen(result));
			i++;
		}
	}
}

void	expand_tokens(t_shell *shell)
{
	size_t	i;
	char	new_token[4096];

	i = 0;
	if (shell->found_error == true)
		return ;
	ft_memset(new_token, '\0', 4096);
	while (shell->tokens[i])
	{
		if (has_path(shell->tokens[i]) == true)
		{
			check_expansion(shell, shell->tokens[i], new_token);
			free(shell->tokens[i]);
			shell->tokens[i] = ft_strdup(new_token);
			if (!shell->tokens[i])
				malloc_fail(shell, "expand tokens");
		}
		i++;
	}
}
