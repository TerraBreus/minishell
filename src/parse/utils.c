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

void	skip_space(char *input, size_t *i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
}

void	skip_litteral(char *str, size_t *i)
{
	if (str[*i] == '\'')
	{
		while (str[*i] != '\'')
			(*i)++;
		(*i)++;
	}
}

void	cleanup_shell(t_shell *shell)
{
	size_t	i;

	i = 0;
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
