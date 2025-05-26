/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:01:43 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 17:04:50 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_meta_char(t_shell *shell, char c)
{
	if (c == '{'
		|| c == '}'
		|| c == '`'
		|| c == '~'
		|| c == '&'
		|| c == ';'
		|| c == '*'
		|| c == '['
		|| c == ']'
		|| c == '\\'
		|| c == '+'
		|| c == '#')
	{
		syntax_error(shell, &c);
		return (true);
	}
	else
		return (false);
}

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
