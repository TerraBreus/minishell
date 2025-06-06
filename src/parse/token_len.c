/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:42:02 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_operator(t_shell *shell, char *input, size_t *i)
{
	if (is_operator(input[*i + 1]))
	{
		if (input[*i] == '|')
			shell->found_error = true;
		if (input[*i] != input[*i + 1])
			shell->found_error = true;
		else
			*i += 2;
	}
	else
		*i += 1;
	if (shell->found_error == true)
		syntax_error(shell, OPERATOR_ERROR);
}

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
		|| c == '#'
		|| c == '^'
		|| c == '('
		|| c == ')')
	{
		subject_error(shell, c);
		return (true);
	}
	else
		return (false);
}

static void	quote_str(t_shell *shell, char *input, size_t *i)
{
	char quote;

	quote = input[*i];
	*i += 1;
	while (input[*i]
		&& input[*i] != quote)
		*i += 1;
	if (input[*i] == quote)
		*i += 1;
	else
		syntax_error(shell, "UNCLOSED QUOTE");
}

static void	token_word(t_shell *shell, char *input, size_t *i)
{
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i])
		&& !is_meta_char(shell, input[*i]))
	{
		if (input[*i] && is_quote(input[*i]))
			quote_str(shell, input, i);
		else
			*i += 1;
	}
}

void	token_len(t_shell *shell, char *input, size_t *i)
{
	if (is_meta_char(shell, input[*i]))
		return ;
	if (is_operator(input[*i]))
		token_operator(shell, input, i);
	else
		token_word(shell, input, i);
}
