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

extern char	**environ;

int	env_init(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (environ[i])
		i++;
	shell->env_copy = malloc(sizeof(char *) * (i + 1));
	shell->exp_copy = malloc(sizeof(char *) * (i + 1));
	if (!shell->env_copy || !shell->exp_copy)
		return (malloc_fail(shell, "env init"), FAILURE);
	i = 0;
	while (environ[i])
	{
		shell->env_copy[i] = ft_strdup(environ[i]);
		shell->exp_copy[i] = ft_strdup(environ[i]);
		if (!shell->env_copy[i] || !shell->exp_copy[i])
			return (malloc_fail(shell, "env_copy[i]"), FAILURE);
		i++;
	}
	shell->env_copy[i] = NULL;
	shell->exp_copy[i] = NULL;
	bubble_sort(shell->exp_copy, i);
	return (SUCCES);
}
