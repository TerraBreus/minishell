/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:53:33 by masmit            #+#    #+#             */
/*   Updated: 2025/06/18 17:54:18 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_from_arr(t_shell *shell, size_t i)
{
	free(shell->tokens[i]);
	while (shell->tokens[i + 1])
	{
		shell->tokens[i] = shell->tokens[i + 1];
		i++;
	}
	shell->tokens[i] = NULL;
}

void	rm_empty(t_shell *shell)
{
	size_t	i;
	char	*new_token;

	i = 0;
	if (shell->found_error == true)
		return ;
	while (shell->tokens[i])
	{
		if (has_path(shell->tokens[i]) == true)
		{
			new_token = check_expansion(shell, shell->tokens[i]);
			if (new_token[0] == '\0')
				remove_from_arr(shell, i);
			free(new_token);
		}
		i++;
	}
}
