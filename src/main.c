/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/04/24 13:33:06 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_here(void)
{
	return ;
}

void	cleanup_wip(void)
{
	exit(EXIT_FAILURE);
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
		input = readline("minishell$ ");
		if (*input)
		{
			token_list = tokenize_input(input);
			free(input);
			print_tokens(token_list);
			exec_here();
			ft_lstclear(&token_list, token_del);
		}
	}
}
