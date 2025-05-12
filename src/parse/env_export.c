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

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**bubble_sort(char **arr, int size)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		swapped = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				swap(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
	return (arr);
}

void	print_export_list(char **env_copy)
{
	size_t	i;
	char	**temp_arr;

	i = 0;
	while (env_copy[i])
		i++;
	temp_arr = bubble_sort(env_copy, i);
	i = 0;
	while (temp_arr[i])
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		write(STDOUT_FILENO, env_copy, sizeof(env_copy));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

// just pass arg with '=' inside, ill do the rest
// on no next arg export behaves differently, also handled
void	my_export(t_shell *shell, char *arg)
{
	size_t	i;
	size_t	env;

	env = 0;
	i = 0;
	if (!arg)
		print_export_list(shell->env_copy);
	while (arg[i] && arg[i] != '=')
	{
		if (valid_filename(arg[i]) == TRUE)
			i++;
		else
		{
			write(STDOUT_FILENO, EXPORT_ERROR, 57);
			return ;
		}
	}
	while (shell->env_copy[env])
		env++;
	shell->env_copy = ft_realloc(shell->env_copy,
			sizeof(char *) * env,
			sizeof(char *) * (env + 2));
	if (!shell->env_copy)
		malloc_fail(shell, "export var and value");
	shell->env_copy[env] = arg;
}
