# include "minishell.h" 

static void	write_and_free(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

static char	*process_heredoc_line(t_shell *shell, char *input,
				char *hd_string, char *delim)
{
	char	*new_hd;
	char	*expanded;

	if (!input)
		return (hd_string);
	new_hd = ft_strjoin(hd_string, input);
	free(hd_string);
	free(input);
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

static void	run_heredoc(t_shell *shell, int pfd[2], char *delim)
{
	char	*input;
	char	*hd_string;

	rl_clear_history();
	while (true)
	{
		input = readline("> ");
		if (!input)
			sigquit_hd(hd_string, pfd, delim);
		if (ft_strcmp(input, delim) == 0)
		{
			free(input);
			break ;
		}
		hd_string = ft_strdup("");
		if (!hd_string)
			malloc_fail(shell, "tokenize heredoc");
		hd_string = process_heredoc_line(shell, input, hd_string, delim);
		if (!hd_string)
			malloc_fail(shell, "process heredoc line");
		write_and_free(hd_string, pfd[1]);
	}
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
		run_heredoc(shell, pfd, r->filename_path);
	close(pfd[1]);
    waitpid(pid, &status, 0);
	if (sigint_hd(status) == true)
		return (close(pfd[0]), -1);
	r->heredoc_fd = pfd[0];
	return (0);
}

