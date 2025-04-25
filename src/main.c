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

void	if_error(t_list *token_list)
{
	t_token_data	*data;

	if (!token_list || !token_list->content)
		return ;
	data = (t_token_data *)token_list->content;
	if (data && data->error)
		print_tokens(token_list);
}

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
		if (!input)
			break;
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		token_list = tokenize_input(input);
		free(input);
		if (token_list)
		{
			print_tokens(token_list);
			syntax_check(token_list);
			if_error(token_list);
			exec_here();
			ft_lstclear(&token_list, token_del);
		}
	}
	return (0);
}
