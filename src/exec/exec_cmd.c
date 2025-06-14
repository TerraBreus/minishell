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

static char	*find_full_path(char *paths[], char *cmd)
{
	char	*addendum;
	char	*path;
	int		i;

	if (paths == NULL)
		return (ft_strdup(cmd));
	addendum = ft_strjoin("/", cmd);
	if (addendum == NULL)
		return (NULL);
	i = -1;
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], addendum);
		if (path == NULL)
			return (free(addendum), NULL);
		if (access(path, F_OK) == 0)
			return (free(addendum), path);
		free(path);
	}
	free(addendum);
	return (ft_strdup(cmd));
}

static char	**create_possible_paths(char *envp[])
{
	int		i;
	char	**possible_paths;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	}
	if (envp[i] == NULL)
		return (envp);
	possible_paths = ft_split(envp[i] + 5, ':');
	if (possible_paths == NULL)
		return (NULL);
	return (possible_paths);
}

static void	free_paths(char **possible_paths)
{
	int		i;

	i = -1;
	if (possible_paths != NULL)
	{
		while (possible_paths[++i] != NULL)
			free(possible_paths[i]);
		free(possible_paths);
	}
}

bool	relative_path(char *path)
{
	if (*path == '.')
		return (true);
	return (false);
}

int	exec_cmd(char **cmd_and_flags, char **envp)
{
	char	**possible_paths;
	char	*path;
	int		error_code;

	if (cmd_and_flags == NULL 
			|| cmd_and_flags[0] == NULL
			|| cmd_and_flags[0][0] == '\0')
		exit(0);
	if (relative_path(cmd_and_flags[0]) == true)
		path = cmd_and_flags[0];
	else
	{
		//Should probably put this in a function called (find_path) or smth
		possible_paths = create_possible_paths(envp);
		if (possible_paths == NULL)
			return (-1);
		if (possible_paths == envp)
			possible_paths = NULL;
		if (cmd_and_flags == NULL)
			return (free_paths(possible_paths), -1);
		path = find_full_path(possible_paths, cmd_and_flags[0]);
		free_paths(possible_paths);
		if (path == NULL)
			return (-1);
	}
	//Just for finesse. A small command checking whether the path is simply a directory
	//If yes, print an error message and exit with status 126. 
	//(zsh treats this the same as EACESS but bash doesn't...)
	execve(path, cmd_and_flags, envp);
	error_code = print_error(path);
	free(path);
	exit(error_code);
}
