/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_cmd.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:19:19 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:19:26 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

// it took god 6 days to create the earth,
//  and 7 to create holy bash
#include "minishell.h"

static void	my_exit(t_shell *shell, t_cmd *exec)
{
	cleanup_env(shell);
	cleanup_shell(shell);
	cleanup_struct(&exec);
	exit(EXIT_SUCCESS);
}

void	exec_builtin(t_shell *shell, t_cmd *exec)
{
	t_cmd	*current;

	current = exec;
	if (ft_strncmp(current->argv[0], "echo", 5) == 0)
		my_echo(current->argv);
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		my_cd(shell, current->argv);
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		my_pwd(shell);
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		my_export(shell, current->argv);
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		my_env(shell);
	else if (ft_strncmp(current->argv[0], "unset", 4) == 0)
		my_unset(shell, current->argv);
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		my_exit(shell, exec);
}

int	builtin_cmd(t_shell *shell, t_cmd *cmd_list, t_pipe *pipe_data)
{
	if (pipe_data != NULL)
	{
		if (setup_pipe_builtin(pipe_data, cmd_list->type) == -1)
			exit(EXIT_FAILURE);			//TODO
	}
	if (setup_redir(cmd_list->redirection) == -1)
		exit(EXIT_FAILURE);		//TODO
	return (builtin(shell, &cmd_list));
}