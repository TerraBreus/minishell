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

void	skip_spaces(char *input, int *index)
{
	while (input[*index] && input[*index] == ' ')
		(*index) += 1;
}

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
