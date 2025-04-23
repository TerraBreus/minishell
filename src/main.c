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

void	cleanup_wip(void)
{
	exit(EXIT_FAILURE);
}

void	display_prompt(void)
{
	write(1, "minishell$ ", 11);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*token_list;
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	while (true)
	{
		display_prompt();
		input = readline("");
		if (syntax_check(input) == FAILURE)
		{
			printf("syntax error\n");
			cleanup_wip();
		}
		if (*input)
		{
			token_list = tokenize_input(input);
			free(input);
			print_tokens(token_list);
			ft_lstclear(&token_list, token_del);
		}
	}
}
