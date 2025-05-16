#include "minishell.h"

int	exec_cmd(char **cmd_and_flags, char **envp, int last_read_end)
{
	char	**possible_paths;
	char	*path;

	close(last_read_end);
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
	return (0);
}
