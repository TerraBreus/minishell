/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:46:18 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 17:16:41 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_shell *shell)
{
	char	*input;

	input = readline("$>");
	tokenize(shell, input);
	expand_tokens(shell, shell->tokens);
	free(input);
	cleanup_shell(shell);
}
