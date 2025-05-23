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

static void	do_heredoc(t_shell *shell, char *input, size_t *i)
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
		if (input[*i] == '|')
			shell->found_error = true;
		if (input[*i] != input[*i + 1])
			shell->found_error = true;
		else if (is_heredoc(input, i))
			do_heredoc(shell, input, i);
		else
			*i += 2;
	}
	else
		*i += 1;
	if (shell->found_error == true)
		syntax_error(shell, OPERATOR_ERROR);
}
