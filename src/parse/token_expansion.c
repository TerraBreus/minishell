/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:52:31 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_var(t_custom_env *my_env, char *input, size_t *i)
{
	char	*path;
	char	*var_name;
	size_t	start;

	(*i)++;
	start = *i;
	if (input[*i] == '?')
		return (ft_itoa(0));
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (start != *i)
	{
		var_name = ft_substr(input, start, *i - start);
		printf("%s", var_name);
		path = my_getenv(my_env, var_name);
		if (path)
			return (free(var_name), ft_strdup(path));
		else
			return (ft_strdup(""));
	}
	return (ft_strdup("$"));
}

static bool	is_path(char *token, size_t *i)
{
	if (token[*i])
	{
		if (token[*i] == '$'
			&& (token[*i + 1] == '_'
			|| token[*i + 1] == '?'
			|| ft_isalnum(token[*i + 1])))
			return (true);
	}
	return (false);
}

static void	skip_litteral(char *token, size_t *i)
{
	if (!token || !token[*i])
		return ;
	if (token[0] == '\'')
	{
		(*i)++;
		while(token[*i] != '\'')
			(*i)++;
		(*i)++;
	}
}

static bool	has_path(char *token)
{
	size_t	i;

	i = 0;
	skip_litteral(token, &i);
	if (!token || !token[i])
		return (false);
	while (token[i])
	{
		if (token[i] == '$'
			&& (token[i + 1] == '_'
			|| token[i + 1] == '?'
			|| ft_isalnum(token[i + 1])))
			return (true);
		i++;
	}
	return (false);
}

char	*insert_path(char *token, t_custom_env *env)
{
	size_t	i;
	size_t	start;
	char	*expanded;
	char	*tmp;

	i = 0;
	start = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (token[i])
	{
		skip_litteral(token, &i);
		if (is_path(token, &i))
			expanded = ft_strjoin_and_free(expanded, expand_var(env, token, &i));
		else
		{
			start = i;
			while (token[i] && token[i] != '$' && token[i] != '\'')
				i++;
			tmp = ft_substr(token, start, i - start);
			expanded = ft_strjoin_and_free(expanded, tmp);
		}
	}
	return (expanded);
}
