/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: terrabuntu <terrabuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/09 16:17:24 by terrabuntu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(char *input)
{
	if (!input)
		exit(EXIT_SUCCESS);
}

int	close_and_return(int in, int out)
{
	close(in);
	close(out);
	return (-1);
}

int	save_or_restore_io(int restore_or_save)
{
	static int	copy_in;
	static int	copy_out;

	if (restore_or_save == SAVE)
	{
		copy_in = dup(STDIN_FILENO);
		copy_out = dup(STDOUT_FILENO);
		return (0);
	}
	else if (restore_or_save == RESTORE)
	{
		if (dup2(copy_in, STDIN_FILENO) == -1)
			return (close_and_return(copy_in, copy_out));
		if (dup2(copy_out, STDOUT_FILENO) == -1)
			return (close_and_return(copy_in, copy_out));
		close(copy_in);
		close(copy_out);
		return (0);
	}
	else 
		return (-1);
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
		save_or_restore_io(SAVE);
		exec_cmd_list(cmd_list, my_env);
		save_or_restore_io(RESTORE);
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
