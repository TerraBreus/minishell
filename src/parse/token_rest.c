/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:34:58 by masmit           ###   ########.fr       */
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
		|| c == '\\')
	{
		syntax_error(shell, &c);
		return (true);
	}
	else
		return (false);
}

static void	make_key(t_shell *shell, char *input, size_t *i)
{
	*i += 1;
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i])
		&& !is_meta_char(shell, input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
			token_quote(shell, input, i);
		else
			*i += 1;
	}
}

static void	token_word(t_shell *shell, char *input, size_t *i)
{
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i])
		&& !is_meta_char(shell, input[*i])
		&& input[*i] != '\''
		&& input[*i] != '"')
	{
		*i += 1;
		if (input[*i] == '=')
			make_key(shell, input, i);
	}
}

void	tokenize_input_len(t_shell *shell, char *input, size_t *i)
{
	if (is_quote(input[*i]))
		token_quote(shell, input, i);
	else if (is_meta_char(shell, input[*i]))
		return ;
	else if (is_operator(input[*i]))
		token_operator(shell, input, i);
	else
		token_word(shell, input, i);
}
