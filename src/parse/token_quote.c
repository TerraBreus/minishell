/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/05/28 11:41:59 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_extension(char *input, size_t *i)
{
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i]))
		*i += 1;
}

static void	string_interpolated(t_shell *shell, char *input, size_t *i)
{
	*i += 1;
	while (input[*i]
		&& input[*i] != '"')
		*i += 1;
	if (input[*i] == '"')
		*i += 1;
	else
		syntax_error(shell, "UNCLOSED QUOTE");
}

static void	string_litteral(t_shell *shell, char *input, size_t *i)
{
	*i += 1;
	while (input[*i]
		&& input[*i] != '\'')
		*i += 1;
	if (input[*i] == '\'')
		*i += 1;
	else
		syntax_error(shell, "UNCLOSED QUOTE");
}

void	token_quote(t_shell *shell, char *input, size_t *i)
{
	if (input[*i])
	{
		if (input[*i] == '\'')
			string_litteral(shell, input, i);
		else
			string_interpolated(shell, input, i);
	}
	if (shell->found_error == true)
		return ;
	token_extension(input, i);
}
