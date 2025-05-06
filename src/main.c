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
	t_cmd	*cmd_list;

	token_list = NULL;
	cmd_list = NULL;
	input = readline("minishell$ ");
	ctrl_d(input);
	if (*input != '\0')
		token_list = tokenize_input(input);
	free(input);
	if (token_list)
	{
		token_expansion(token_list, my_env);
		cmd_list = cmd_struct(token_list);
		if (!cmd_list)
			malloc_fail("cmd_list in loop", my_env, token_list);
		print_cmd_list(cmd_list);
		cleanup_cmd_list(cmd_list);
		ft_lstclear(&token_list, token_del);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_custom_env	*my_env;

	(void)argc;
	(void)argv;
	my_env = shell_env_init(env);
	if (my_env == NULL)
		return (EXIT_FAILURE);
	while (true)
		loop(my_env);
	cleanup_env(my_env);
	return (0);
}
