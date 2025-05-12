#include "minishell.h"

char	*find_full_path(char *paths[], char *cmd)
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

char	**create_possible_paths(char *envp[])
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

void	free_paths(char **possible_paths)
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
