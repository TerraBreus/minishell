/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exec_cmd.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/04 17:22:47 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/04 17:22:50 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_cmd(char **cmd_and_flags, char **envp)
{
	char	**possible_paths;
	char	*path;

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
	execve(path, cmd_and_flags, envp);
	perror(path);
	free(path);
	exit(EXIT_FAILURE);
}
