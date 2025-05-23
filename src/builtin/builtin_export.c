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

int	find_index(char **env, char *str, size_t len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0
			&& env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static bool	valid_filename(t_shell *shell, char *str)
{
	size_t	i;

	i = 0;
	while (is_filename_char(str[i]))
		i++;
	if ((str[i] == '\0' || str[i] == '=') && i != 0)
		return (true);
	else
		filename_invalid(shell, str);
	return (false);
}

static void	add_to_export(t_shell *shell, char *str)
{
	size_t	i;

	i = 0;
	while (shell->exp_copy[i])
		i++;
	shell->exp_copy = ft_realloc(shell->exp_copy,
			sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2));
	if (!shell->exp_copy)
		malloc_fail(shell, "add to export");
	shell->exp_copy[i] = ft_strdup(str);
	if (!shell->exp_copy[i])
		malloc_fail(shell, "add to export");
	shell->exp_copy[i + 1] = NULL;
}

static void	remove_from_export(t_shell *shell, char *str)
{
	size_t	i;
	size_t	name_len;
	char	*old_name;

	name_len = 0;
	while (str[name_len] != '=')
		name_len++;
	old_name = ft_substr(str, 0, name_len);
	if (!old_name)
		malloc_fail(shell, "remove from export");
	i = 0;
	while (shell->exp_copy[i])
	{
		if (ft_strncmp(shell->exp_copy[i], old_name, name_len) == 0
			&& shell->exp_copy[i][name_len] == '\0')
		{
			remove_arg(shell->exp_copy, &i);
			break ;
		}
		i++;
	}
	free(old_name);
}

void	my_export(t_shell *shell, char **arg_list)
{
	size_t	i;

	i = 1;
	if (!arg_list[i])
	{
		just_print(shell->exp_copy);
		return ;
	}
	while (arg_list[i])
	{
		if (valid_filename(shell, arg_list[i]))
		{
			if (ft_strchr(arg_list[i], '='))
			{
				add_to_env(shell, arg_list[i]);
				remove_from_export(shell, arg_list[i]);
			}
			else if (find_index(shell->env, arg_list[i],
					ft_strlen(arg_list[i])) == -1)
				add_to_export(shell, arg_list[i]);
		}
		i++;
	}
}
