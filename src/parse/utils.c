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

void	skip_space(char *input, size_t *i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		*i += 1;
}

void	skip_litteral(char *str, size_t *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] != '\'')
			*i += 1;
		*i += 1;
	}
}

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

void	cleanup_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->env_copy)
	{
		while (shell->env_copy[i])
		{
			free(shell->env_copy[i]);
			i++;
		}
		free(shell->env_copy);
		shell->env_copy = NULL;
	}
	if (shell->exp_copy)
	{
		while (shell->exp_copy[i])
		{
			free(shell->exp_copy[i]);
			i++;
		}
		free(shell->exp_copy);
		shell->exp_copy = NULL;
	}
	free(shell->old_pwd);
}

void	print_tokens(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->tc)
	{
		printf("%s\n", shell->tokens[i]);
		i++;
	}
}
