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

void	print_tokens(t_list *head)
{
	t_token_data	*data;
	int				i;

	i = 0;
	printf("\nTokens:\n");
	while (head)
	{
		data = head->content;
		printf("%d: [", i++);
		if (data->token)
			printf("%s", data->token);
		else
			printf("(null)");
		printf("] (s:%d, d:%d)\n", data->in_singles, data->in_doubles);
		head = head->next;
	}
}

bool	syntax_check(const char *input)
{
	size_t	index;
	size_t	singles_count;
	size_t	doubles_count;

	index = 0;
	singles_count = 0;
	doubles_count = 0;
	while (input[index])
	{
		if (input[index] == '\'')
			singles_count++;
		if (input[index] == '"')
			doubles_count++;
		index++;
	}
	if (singles_count % 2 != 0 || doubles_count % 2 != 0)
		return (FAILURE);
	return (SUCCES);
}

bool	is_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

bool	is_operator_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}
