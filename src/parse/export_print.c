/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:44 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(char **arr, size_t size)
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
}

static void	on_fail(t_shell *shell, char **temp_arr, size_t *i)
{
	if (!temp_arr[*i])
	{
		while ((*i)-- > 0)
			free(temp_arr[*i]);
		free(temp_arr);
		malloc_fail(shell, "print_export_list");
		return ;
	}
}

bool	print_export_list(t_shell *shell, char **env_copy)
{
	char	**temp_arr;
	size_t	i;

	i = 0;
	while (env_copy && env_copy[i])
		i++;
	temp_arr = malloc(sizeof(char *) * (i + 1));
	if (!temp_arr)
		return (malloc_fail(shell, "print export list"), NULL);
	i = 0;
	while (env_copy[i])
	{
		temp_arr[i] = ft_strdup(env_copy[i]);
		if (!temp_arr[i])
			return (on_fail(shell, temp_arr, &i), NULL);
		i++;
	}
	temp_arr[i] = NULL;
	bubble_sort(temp_arr, i);
	just_print(temp_arr);
	free(temp_arr);
	return (true);
}
