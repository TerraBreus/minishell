# include "minishell.h" 

static void	write_and_free(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

static void	run_heredoc(int pfd[2], t_redir *r)
{
	char	*input;

	sig_child();
	while (true)
	{
		input = readline("HERE_DOC: ");
		if (!input)
			sigquit_hd(pfd, r->filename_path);
		if (ft_strcmp(input, r->filename_path) == 0)
		{
			free(input);
			break;
		}
		write_and_free(input, pfd[1]);
	}
	close(pfd[1]);
	exit(0);
}

int	setup_heredoc(t_redir *r)
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
		run_heredoc(pfd, r);
	close(pfd[1]);
    waitpid(pid, &status, 0);
	if (sigint_hd(status) == true)
		return (close(pfd[0]), -1);
	r->heredoc_fd = pfd[0];
	return (0);
}

