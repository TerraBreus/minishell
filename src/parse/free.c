/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:17 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_shell(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (!shell->tokens)
		return ;
	while (i < shell->tc)
	{
		free(shell->tokens[i]);
		i++;
	}
	free(shell->tokens);
	shell->tokens = NULL;
}

void	free_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	cleanup_env(t_shell *shell)
{
	free_arr(shell->env);
	shell->env = NULL;
	free_arr(shell->export);
	shell->export = NULL;
	if (shell->old_pwd)
		free(shell->old_pwd);
	shell->old_pwd = NULL;
}

void	quick_clean(t_shell *shell)
{
	cleanup_shell(shell);
	cleanup_env(shell);
}
