/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 16:17:25 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/19 16:17:27 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_check(t_shell *shell, t_cmd *exec, char **args)
{
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, EXIT_ERR, ft_strlen(EXIT_ERR));
		quick_clean(shell);
		cleanup_struct(&exec);
		exit(1);
	}
}

static void	my_exit(t_shell *shell, t_cmd *exec, char **args)
{
	uint8_t	status;
	int		i;

	i = 0;
	status = 0;
	arg_check(shell, exec, args);
	if (args[1])
	{
		if (args[1][i] == '+' || args[1][i] == '-')
			i++;
		while (ft_isdigit(args[1][i]))
			i++;
		if (args[1][i] != '\0')
		{
			ft_putstr_fd("minishell: numeric argument required\n",
				STDERR_FILENO);
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
