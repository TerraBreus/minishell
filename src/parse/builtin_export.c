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

static void	add_var(t_shell *shell, char *arg)
{
	size_t	i;

	i = 0;
	while (shell->env_copy[i])
		i++;
	shell->env_copy = ft_realloc(shell->env_copy,
			sizeof(char *) * i,
			sizeof(char *) * (i + 2));
	if (!shell->env_copy)
	{
		malloc_fail(shell, "add var");
		return ;
	}
	shell->env_copy[i] = ft_strdup(arg);
	if (!shell->env_copy[i])
	{
		malloc_fail(shell, "add var");
		return ;
	}
	shell->env_copy[i + 1] = NULL;
}

static void	update_var(
	t_shell *shell, int index, char *arg)
{
	free(shell->env_copy[index]);
	shell->env_copy[index] = ft_strdup(arg);
	if (!shell->env_copy[index])
		malloc_fail(shell, "add_to_env");
}

static int	find_index(t_shell *shell, const char *arg, size_t key_len)
{
	int	i;

	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], arg, key_len) == 0
			&& shell->env_copy[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	add_to_env(t_shell *shell, char *arg)
{
	size_t	key_len;
	int		index;

	if (ft_strchr(arg, '=') != 0)
		key_len = ft_strchr(arg, '=') - arg;
	else
		key_len = ft_strlen(arg);
	index = find_index(shell, arg, key_len);
	if (index != -1)
		update_var(shell, index, arg);
	else
		add_var(shell, arg);
}

// just pass arg with '=' inside, ill do the rest
// on no arg export prints same list as env but sorted
void	my_export(t_shell *shell, char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
	{
		print_export_list(shell, shell->env_copy);
		return ;
	}
	while (arg[i] && arg[i] != '=')
	{
		if (valid_filename(arg[i]) == true)
			i++;
		else
		{
			write(STDOUT_FILENO, EXPORT_ERROR, ft_strlen(EXPORT_ERROR));
			shell->last_errno = 1;
			return ;
		}
	}
	add_to_env(shell, arg);
}
// TODO update add_to_env for exporting local vars
