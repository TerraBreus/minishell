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

static char	*handle_non_var_part(char *str, size_t *i)
{
	size_t	start;
	char	*part;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	part = ft_substr(str, start, *i - start);
	return (part);
}

static char	*expand_var(t_shell *shell, char *str, size_t *i)
{
	char	*path;
	char	*var_name;
	size_t	start;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->last_errno));
	}
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	if (start != *i)
	{
		var_name = ft_substr(str, start, *i - start);
		path = my_getenv(shell, var_name);
		free(var_name);
		if (path)
			return (path);
		else
			return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}

static char	*check_expansion(t_shell *shell, char *str)
{
	size_t	i;
	char	*expanded;
	char	*part;
	bool	in_singles;
	bool	in_doubles;

	i = 0;
	in_singles = false;
	in_doubles = false;
	expanded = ft_strdup("");
	if (!expanded)
		malloc_fail(shell, "check_expansion");
	while (str[i])
	{
		update_bools(str[i], &in_singles, &in_doubles);
		if (!in_singles && is_path(str, &i))
			part = expand_var(shell, str, &i);
		else
			part = handle_non_var_part(str, &i);
		expanded = ft_strjoin_and_free(expanded, part);
	}
	return (expanded);
}

void	expand_tokens(t_shell *shell)
{
	size_t	i;
	char	*new_token;

	i = 0;
	if (shell->found_error == TRUE)
		return ;
	while (shell->tokens[i])
	{
		if (has_path(shell->tokens[i]))
		{
			new_token = check_expansion(shell, shell->tokens[i]);
			free(shell->tokens[i]);
			shell->tokens[i] = new_token;
		}
		i++;
	}
}
