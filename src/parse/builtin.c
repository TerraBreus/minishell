/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/07 16:13:37 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// it took god 6 days to create the earth,
//  and 7 to create holy bash
#include "minishell.h"

static void	my_exit(t_shell *shell, t_cmd *exec, char **args)
{
	uint8_t	status;
	int		i;

	i = 0;
	status = 0;
	if (args[1] && args[2])
		write(STDERR_FILENO, EXIT_ERR, ft_strlen(EXIT_ERR));
	if (args[1])
	{
		if (args[1][i] == '+' || args[1][i] == '-')
			i++;
		while (ft_isdigit(args[1][i]))
			i++;
		if (args[1][i] != '\0')
		{
			printf("minishell: %s: numeric argument required\n", args[1]);
			status = 2;
		}
		else
			status = ft_atoi(args[1]) % 256;
	}
	quick_clean(shell);
	cleanup_struct(&exec);
	exit(status);
}

int	builtin(t_shell *shell, t_cmd **exec)
{
	t_cmd	*current;

	current = *exec;
	if (shell->found_error == true || !current->argv[0])
		return (-1);
	if (ft_strncmp(current->argv[0], "echo", 5) == 0)
		return (my_echo(current->argv));
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		return (my_cd(shell, current->argv));
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		return (my_pwd(shell));
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		return (my_export(shell, current->argv));
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		return (my_env(shell));
	else if (ft_strncmp(current->argv[0], "unset", 4) == 0)
		return (my_unset(shell, current->argv));
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		my_exit(shell, *exec, current->argv);
	return (BUILTIN_NOT_FOUND);
}
