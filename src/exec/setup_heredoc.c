# include "minishell.h" 

static void	write_and_free(char *input, int fd)
{
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	free(input);
}

char	*tokenize_hd(t_shell *shell, char *input, char *hd_string, char *delim)
{
	char	*new_hd;
	char	*expanded;
	
	new_hd = ft_strjoin(hd_string, input);
	free(hd_string);
	if (!new_hd)
		malloc_fail(shell, "tokenize heredoc");
	if (delim[0] != '\'' && delim[0] != '"')
	{
		expanded = check_expansion(shell, new_hd);
		free(new_hd);
		return (expanded);
	}
	return (new_hd);
}

static char	*process_heredoc_line(
	t_shell *shell, char *input, char **hd_string, char *delim)
{
	char	*new_hd;
	char	*to_write;

	new_hd = tokenize_hd(shell, input, *hd_string, delim);
	if (!new_hd)
		return (NULL);
	to_write = new_hd;
	if (delim[0] == '\'' || delim[0] == '"')
		to_write = input;
	if (*hd_string == new_hd)
		write_and_free(input, NULL);
	else
		write_and_free(input, *hd_string);
	return (new_hd);
}

static void	run_heredoc(t_shell *shell, int pfd[2], t_redir *r)
{
	char	*input;
	char	*hd_string;

	hd_string = ft_strdup("");
	if (!hd_string)
		malloc_fail(shell, "tokenize heredoc");
	rl_clear_history();
	while (true)
	{
		input = readline("> ");
		if (!input)
			sigquit_hd(hd_string, pfd, r->filename_path);
		if (ft_strcmp(input, r->filename_path) == 0)
		{
			free(input);
			break;
		}
		hd_string = process_heredoc_line(shell, input, &hd_string,
				r->filename_path);
		if (!hd_string)
			malloc_fail(shell, "process heredoc line");
	}
	free(hd_string);
	close(pfd[1]);
	exit(0);
}

int	setup_heredoc(t_shell *shell, t_redir *r)
{
	/*
	 * 1. Create a pipe
	 * 2. readline input from user
	 * 3. check if delimiter from user is in readline
	 * 	N: Write to pipe and repeat step 2. Also free input
	 * 	Y: Write to pipe and continue. Also free input.
	 * 4. Save pipe_read to the redirection structure.
	 * 5. Close pipe_write side.
	*/

	int	pfd[2];
	pid_t	pid;
	int	status;

	if (pipe(pfd) == -1)
		exit(EXIT_FAILURE);		//TODO
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);		//TODO Forking failure.
	if (pid == 0)
		run_heredoc(shell, pfd, r);
	close(pfd[1]);
    waitpid(pid, &status, 0);
	if (sigint_hd(status) == true)
		return (close(pfd[0]), -1);
	r->heredoc_fd = pfd[0];
	return (0);
}

