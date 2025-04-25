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

void	this_shoudlnt_happen(t_list *head, int *i)
{
	printf("%d: [(null content)]\n", *(i)++);
	head = head->next;
}

void	print_tokens(t_list *head)
{
	t_token_data	*data;
	int				i;

	i = 0;
	printf("\nTokens:\n");
	while (head != NULL)
	{
		if (head->content == NULL)
			this_shoudlnt_happen(head, &i);
		data = (t_token_data *)head->content;
		printf("%d: [", i++);
		if (data->token != NULL)
			printf("%s", data->token);
		else
			printf("(null)");
		printf("]\n");
		if (data->error != NULL)
		{
			printf("[error = %s]\n", data->error);
			return ;
		}
		head = head->next;
	}
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
