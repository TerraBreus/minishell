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

void	ctrl_d(char *input)
{
	if (!input)
		exit(EXIT_SUCCESS);
}


int	main(int argc, char **argv, char **env)
{
	t_custom_env	*my_env;
	t_list			*token_list;
	char	*input;

	(void)argc;
	(void)argv;
	my_env = shell_env_init(env);
	if (!my_env)
		return (EXIT_FAILURE);
	while (true)
	{
		input = readline("minishell$ ");
		ctrl_d(input);
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
			ft_lstclear(&token_list, token_del);
		}
	}
	cleanup_env(my_env);
	return (0);
}
