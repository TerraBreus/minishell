/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:52:31 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_operator_type(char *token)
{
	if (strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (strcmp(token, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (strcmp(token, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (strcmp(token, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (strcmp(token, ">>") == 0)
		return (TOKEN_APPEND);
	return (TOKEN_WORD);
}
