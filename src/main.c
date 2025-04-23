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

void	display_prompt(void)
{
	write(1, "minishell$ ", 11);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*token_list;

	(void)argc;
	(void)argv;
	(void)env;
	char	*input;
	while (true)
	{
		display_prompt();
		input = readline("");
		token_list = tokenize_input(input);
		free(input);
		if (!token_list)
		{
			// well then we have a problem...
			return (0);
		}
		// parse_tokens();
	}
}
