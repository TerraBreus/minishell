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
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**bubble_sort(char **arr, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	swapped;

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
		write(STDOUT_FILENO, temp_arr[i], ft_strlen(temp_arr[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	add_to_env(t_shell *shell, char *arg)
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
		malloc_fail(shell, "export var and value");
		return ;
	}
	shell->env_copy[i] = arg;
	shell->env_copy[i + 1] = NULL;
}

// just pass arg with '=' inside, ill do the rest
// on no arg export prints same list as env but sorted
void	my_export(t_shell *shell, char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
	{
		print_export_list(shell->env_copy);
		return ;
	}
	while (arg[i] && arg[i] != '=')
	{
		if (valid_filename(arg[i]) == TRUE)
			i++;
		else
		{
			write(STDOUT_FILENO, EXPORT_ERROR, 57);
			shell->last_errno = 1;
			return ;
		}
	}
	add_to_env(shell, arg);
}
