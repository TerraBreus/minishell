/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:14:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(char *input)
{
	if (!input)
		exit(EXIT_SUCCESS);
}

void	loop(t_custom_env *my_env)
{
	char	*input;
	t_list	*token_list;

	token_list = NULL;
	input = readline("minishell$ ");
	ctrl_d(input);
	if (*input == '\0')
		free(input);
	else
	{
		token_list = tokenize_input(input);
		free(input);
	}
	if (token_list)
	{
		print_tokens(token_list);
		token_expansion(token_list, my_env);
		ft_lstclear(&token_list, token_del);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_custom_env	*my_env;

	(void)argc;
	(void)argv;
	if ((my_env = shell_env_init(env)) == NULL)
		return (EXIT_FAILURE);
	while (true)
		loop(my_env);
	cleanup_env(my_env);
	return (0);
}
