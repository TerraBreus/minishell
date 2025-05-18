/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_local.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	add_var(t_shell *shell, char *variable)
// {
// 	size_t	i;

// 	i = 0;
// 	while (shell->exp_copy[i])
// 		i++;
// 	shell->exp_copy = ft_realloc(shell->exp_copy,
// 			sizeof(char *) * (i + 1),
// 			sizeof(char *) * (i + 2));
// 	if (!shell->exp_copy)
// 	{
// 		malloc_fail(shell, "add var");
// 		return ;
// 	}
// 	shell->exp_copy[i] = variable;
// 	shell->exp_copy[i + 1] = NULL;
// }

// static bool	does_var_exist(t_shell *shell, char *variable)
// {
// 	char	*key;
// 	size_t	i;

// 	i = 0;
// 	while (variable[i] && variable[i] != '=')
// 		i++;
// 	key = ft_substr(variable, 0, i);
// 	if (!key)
// 		return (malloc_fail(shell, "does var exist"), NULL);
// 	i = 0;
// 	while (shell->exp_copy[i])
// 	{
// 		if (ft_strncmp(shell->exp_copy[i], key, ft_strlen(key))
// 			&& shell->exp_copy[i][ft_strlen(key)] == '=')
// 		{
// 			free(shell->exp_copy[i]);
// 			free(key);
// 			shell->exp_copy[i] = ft_strdup(variable);
// 			return (true);
// 		}
// 		i++;
// 	}
// 	free(key);
// 	return (false);
// }

// // before this function call
// void	export_local(t_shell *shell, char *variable)
// {
// 	if (!variable)
// 		return ;
// 	if (does_var_exist(shell, variable) == true)
// 		return ;
// 	else
// 		add_var(shell, variable);
// }
