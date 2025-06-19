/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:22:47 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/10 14:02:50 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *path)
{
	perror(path);
	if (errno == ENOENT)
		return (127);
	if (errno == EACCES)
		return (126);
	if (errno == EISDIR)
		return (126);
	else
		return (1);
}

char	*find_path(char **cmd_and_flags, char **envp)
{
	char	**possible_paths;
	char	*path;

	possible_paths = create_possible_paths(envp);
	if (possible_paths == NULL)
		return (NULL);
	if (possible_paths == envp)
		possible_paths = NULL;
	if (cmd_and_flags == NULL)
		return (free_paths(possible_paths), NULL);
	path = find_full_path(possible_paths, cmd_and_flags[0]);
	free_paths(possible_paths);
	return (path);
}

int	exec_cmd(char **cmd_and_flags, char **envp)
{
	char	*path;
	int		error_code;

	if (cmd_and_flags == NULL
		|| cmd_and_flags[0] == NULL
		|| cmd_and_flags[0][0] == '\0')
		exit(0);
	if (relative_path(cmd_and_flags[0]) == true)
		path = cmd_and_flags[0];
	else
		path = find_path(cmd_and_flags, envp);
	if (path == NULL)
		exit(EXIT_FAILURE);
	execve(path, cmd_and_flags, envp);
	error_code = print_error(path);
	free(path);
	exit(error_code);
}
