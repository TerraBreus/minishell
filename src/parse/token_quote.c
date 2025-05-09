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

static void	token_extension(char *input, size_t *i)
{
	while (input[*i]
		&& input[*i] != '\''
		&& input[*i] != '"'
		&& !is_space(input[*i])
		&& !is_operator(input[*i]))
		(*i)++;
}

static void	string_interpolated(t_shell *shell, char *input, size_t *i)
{
	(*i)++;
	while (input[*i]
		&& input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
		(*i)++;
	else
		shell->found_error = TRUE;
}

static void	string_litteral(t_shell *shell, char *input, size_t *i)
{
	(*i)++;
	while (input[*i]
		&& input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
		(*i)++;
	else
		shell->found_error = TRUE;
}

void	token_quote(t_shell *shell, char *input, size_t *i)
{
	if (input[*i] && input[*i + 1])
	{
		if (input[*i] == '\'')
			string_litteral(shell, input, i);
		else
			string_interpolated(shell, input, i);
	}
	if (shell->found_error == TRUE)
		syntax_error(shell, "UNCLOSED QUOTE");
	token_extension(input, i);
}
