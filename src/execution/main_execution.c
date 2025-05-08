#include "minishell.h"


typedef int (*t_redir_handler)(t_redir *r);

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

int	exec_cmd(char *cmdline, char *envp[])		//TODO we know use a different structure
{
	char	**cmd_and_flags;
	char	**possible_paths;
	char	*path;

	possible_paths = create_possible_paths(envp);
	if (possible_paths == NULL)
		return (-1);
	if (possible_paths == envp)
		possible_paths = NULL;
	if (is_only_space(cmdline) == true)		//TODO
		cmd_and_flags = ft_split(cmdline, ':');
	else
		cmd_and_flags = ft_split(cmdline, ' ');
	if (cmd_and_flags == NULL)
		return (free_paths(possible_paths), -1);
	path = find_full_path(possible_paths, cmd_and_flags[0]);
	free_paths(possible_paths);
	if (path == NULL)
		return (free_paths(cmd_and_flags), -1);
	execve(path, cmd_and_flags, envp);
	perror(path);
	free(path);
	free_paths(cmd_and_flags);
	return (127);
}

//void	child_operation(int i, char **argv, char **envp)
//{
//	int	err_code;
//
//	err_code = exec_cmd(argv[i + 1], envp);
//	close(STDIN_FILENO);
//	close(STDOUT_FILENO);
//	if (err_code == 127)
//		exit(127);
//	exit(EXIT_FAILURE);
//}

int	handle_in(t_redir *r)
{
	int		fd_in;

	fd_in = open(r->filename_path, RD_ONLY);
	if (fd_in == -1)
		return (-1);	//Would be useful to print error message of strerrno;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (-1);
	close(fd_in);
	return (0);
}

int	handle_out(t_redir *r)
{
	int		fd_out;

	fd_out = open(r->filename_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		return (-1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_out);
	return (0);
}

int	handle_append(t_redir *r)
{
	int		fd_append;

	fd_append = open(r->filename_path, O_WRONLY | O_CREAT, 0777);
	if (fd_append == -1)
		return (-1);
	if (dup2(fd_append, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_append);
	return (0);
}

int handle_heredoc(t_redir *r)
{
	if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
		return (-1);
	close(heredoc_fd);
	return (0);
}

int	setup_io(t_redir *redir_data)
{
	static t_redir_handler handlers[] = { //TODO Declare this type in one of the headers.
		handle_in,
		handle_out,
		handle_append,
		handle_heredoc
	};

	while (redir_data != NULL)
	{
		if (redir_data->type < 0 || redir_data->type > 3)
			return (-1);
		if (handlers[redir_data->type](redir_data) == -1)
			return (-1);
		redir_data->next = redir_data;
	}
	return (0);
}

int	exec_cmd_list(t_cmd	*cmd_list)		//TODO: Must also add environment for exec_cmd()
{
	while (cmd_list != NULL)
	{
//		if (cmd_list->next != NULL)
//			create_new_pipe();		//TODO
//		else
//			setup_last_read_pipe();		//TODO
		
		setup_io(cmd_list->redirection);
		
//		if (built_in(*(cmd_list->argv)))	//TODO
//			exec_built_in(cmd_list);	//TODO
//		else
//			exec_cmd(cmd_list);
		exec_cmd(cmd_list);
		cmd_list = cmd_list->next;
	}
	return (0);
}
