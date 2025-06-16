/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/12 14:29:45 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_check(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->found_error == true
		|| !shell->tokens[0]
		|| shell->tokens[0][0] == '\0')
		return ;
	if (is_operator(shell->tokens[shell->tc -1][0])
		|| shell->tokens[0][0] == '|')
	{
		syntax_error(shell, &shell->tokens[i][0]);
		return ;
	}
	while (i < shell->tc -1
		&& shell->found_error == false)
	{
		if (shell->tokens[i][0] == '|'
			&& shell->tokens[i + 1][0] == '|')
			syntax_error(shell, &shell->tokens[i][0]);
		if (redir_type(shell->tokens[i]) != NONE
			&& (redir_type(shell->tokens[i + 1]) != NONE
				|| shell->tokens[i + 1][0] == '|'))
			syntax_error(shell, &shell->tokens[i][0]);
		i++;
	}
}

static void	ambiguous_error(char *bad_filename)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write (STDERR_FILENO, bad_filename, ft_strlen(bad_filename));
	write(STDERR_FILENO, ": ambiguous redirect\n", 22);
}

void	ambiguous_check(t_shell *shell, char **arr)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		if (redir_type(arr[i]) != NONE && redir_type(arr[i]) != HEREDOC)
		{
			if (arr[i + 1])
			{
				temp = check_expansion(shell, arr[i + 1]);
				if (temp[0] == '\0')
				{
					ambiguous_error(arr[i + 1]);
					free(arr[i]);
					arr[i] = ft_strdup("<>");
					if (!arr[i])
						malloc_fail(shell, "ambiguous check\n");
				}
				free(temp);
			}
		}
		i++;
	}
}
