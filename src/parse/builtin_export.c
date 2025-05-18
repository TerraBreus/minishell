/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:44 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_index(char **env, char *str, size_t len)
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

bool	valid_filename(t_shell *shell, char *str)
{
	size_t	i;

	i = 0;
	while (is_filename_char(str[i]))
		i++;
	if (str[i] == '\0' || str[i] == '=')
		return (true);
	else
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		shell->last_errno = 1;
	}
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
			printf("var found\n");
			delete_var(shell->exp_copy, &i);
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
		if (!valid_filename(shell, arg_list[i]))
			continue ;
		if (ft_strchr(arg_list[i], '='))
		{
			add_to_env(shell, arg_list[i]);
			remove_from_export(shell, arg_list[i]);
		}
		else if (find_index(shell->env_copy, arg_list[i],
				ft_strlen(arg_list[i])) == -1)
			add_to_export(shell, arg_list[i]);
		i++;
	}
}
