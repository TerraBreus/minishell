/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:49:09 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 17:00:56 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_key(t_shell *shell, char *input, size_t *i)
{
	*i += 1;
	while (input[*i]
		&& !is_space(input[*i])
		&& !is_operator(input[*i])
		&& !is_meta_char(shell, input[*i]))
	{
		if (is_quote(input[*i]))
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
		&& !is_meta_char(shell, input[*i]))
	{
		*i += 1;
		if (input[*i] == '=')
			make_key(shell, input, i);
	}
}

static int	token_len(t_shell *shell, char *input, size_t *i)
{
	if (is_quote(input[*i]))
		token_quote(shell, input, *i);
	else if (is_meta_char(shell, input[*i]))
		return ;
	else if (is_operator(input[*i]))
		token_operator(shell, input, *i);
	else
		token_word(shell, input, *i);
}

static void	malloc_tokens(t_shell *shell, char *input, size_t *i)
{
	while (*i < ft_strlen(input))
	{
		token_len(shell, input, i);
		shell->tc++;
		skip_space(input, i);
	}
	shell->tokens = ft_calloc(shell->tc + 1, sizeof(char *));
	if (!shell->tokens)
		malloc_fail(shell, "malloc tokens");
	shell->tokens[shell->tc + 1] = NULL;
	shell->tc = 0;
}

void	tokenize(t_shell *shell, char *input)
{
	size_t	i;
	size_t	start;

	i = 0;
	add_history(input);
	skip_space(input, &i);
	malloc_tokens(shell, input, &i);
	i = 0;
	skip_space(input, &i);
	while (i < ft_strlen(input))
	{
		start = i;
		token_len(shell, input, &i);
		shell->tokens[shell->tc] = ft_substr(input, start, i - start);
		if (!shell->tokens[shell->tc])
			malloc_fail(shell, "tokenize");
		shell->tc++;
		skip_space(input, &i);
	}
}
