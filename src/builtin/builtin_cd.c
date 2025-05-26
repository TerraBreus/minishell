/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:14:27 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 13:14:31 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_shell *shell, char *err_token)
{
	ft_putstr_fd(err_token, STDERR_FILENO);
	shell->found_error = true;
	shell->last_errno = 1;
}

static int	update_pwd(t_shell *shell, const char *new_path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = malloc(PATH_MAX);
	new_pwd = malloc(PATH_MAX);
	if (!old_pwd || !new_pwd)
		return (free(new_pwd), free(old_pwd), FAILURE);
	if (getcwd(old_pwd, PATH_MAX) == NULL)
		cd_error(shell, CWD_ERROR);
	if (chdir(new_path) != 0)
	{
		cd_error(shell, PWD_ERROR);
		return (free(new_pwd), free(old_pwd), FAILURE);
	}
	if (getcwd(new_pwd, PATH_MAX) == NULL)
		cd_error(shell, PWD_ERROR);
	free(shell->old_pwd);
	shell->old_pwd = old_pwd;
	free(new_pwd);
	return (SUCCESS);
}

// arg 0 is always cd
int	my_cd(t_shell *shell, char **arg_list)
{
	if (!arg_list[1])
	{
		update_pwd(shell, my_getenv(shell, "HOME"));
		return (0);
	}
	if (arg_list[2])
	{
		cd_error(shell, CD_TOO_MANY_ARGS);
		return (1);
	}
	if (ft_strncmp(arg_list[1], "-", 2) == 0)
	{
		update_pwd(shell, shell->old_pwd);
		my_pwd(shell);
	}
	else
		update_pwd(shell, arg_list[1]);
	return (0);
}
