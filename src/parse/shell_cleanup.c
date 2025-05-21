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
	free_arr(shell->env_copy);
	shell->env_copy = NULL;
	free_arr(shell->exp_copy);
	shell->exp_copy = NULL;
	if (shell->old_pwd)
		free(shell->old_pwd);
	shell->old_pwd = NULL;
}
