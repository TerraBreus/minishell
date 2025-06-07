/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:24:55 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/07 14:36:15 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h" 

static void	write_w_newline(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static void	run_heredoc(t_shell *shell, int pfd[2], char *delim, bool *eof_quote)
{
	char	*input;
	char	*hd_string;

	rl_clear_history();
	sig_child();
	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			sigeof_hd(pfd, delim);
			write_w_newline("", pfd[1]);
			close(pfd[1]);
			exit(1) ;
		}
		if (ft_strcmp(input, delim) == 0)
		{
			free(input);
			break ;
		}
		if (*eof_quote == true)
			hd_string = ft_strdup(input);
		else
			hd_string = check_expansion(shell, input);
		if (!hd_string)
			malloc_fail(shell, "process heredoc line");
		write_w_newline(hd_string, pfd[1]);
		free(hd_string);
		free(input);
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
		run_heredoc(shell, pfd, r->filename_path, &r->filename_quotes);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	if (sigint_hd(status) == -1)
		return (close(pfd[0]), -1);
	r->heredoc_fd = pfd[0];
	return (0);
}

