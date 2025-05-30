# include "minishell.h" 

static void	write_and_free(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	free(str);
}

int	setup_heredoc(t_redir *r) {
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
	char	*input;

	if (pipe(pfd) == -1)
		exit(EXIT_FAILURE);		//TODO
	
	while (true)
	{
		input = readline("HERE_DOC: ");
		if (input == NULL)
			return (-1);		//TODO
		if (ft_strncmp(input, r->filename_path, ft_strlen(input)) == 0)
			break ;
		else
			write_and_free(input, pfd[1]);
	}
	free(input);
	close(pfd[1]);
	r->heredoc_fd = pfd[0];
	return (0);
}

