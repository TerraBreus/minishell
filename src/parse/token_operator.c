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

void	do_heredoc(t_shell *shell, char *input, size_t *i)
{
	(void)input;
	(void)i;
	(void)shell;
	ft_putstr_fd("function not yet implemented", STDOUT_FILENO);
}

static bool	is_heredoc(char *input, size_t *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (true);
	else
		return (false);
}

void	token_operator(t_shell *shell, char *input, size_t *i)
{
	if (is_operator(input[*i + 1]))
	{
		if (input[*i] != input[*i + 1])
			shell->found_error = TRUE;
		else if (is_heredoc(input, i))
			do_heredoc(shell, input, i);
		else
			*i += 2;
	}
	else
		*i += 1;
	if (shell->found_error == true)
		syntax_error(shell, "unknown operator combination");
}
