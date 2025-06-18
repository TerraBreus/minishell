/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:24:55 by zivanov           #+#    #+#             */
/*   Updated: 2025/06/18 18:26:46 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static void	write_w_newline(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static int	empty_hd_line(int pfd[2], char *delim)
{
	write(2, EOF_ERROR, ft_strlen(EOF_ERROR));
	write(2, delim, ft_strlen(delim));
	write(2, "'\n", 2);
	close(pfd[1]);
	return (1);
}

static char	*new_delim(t_shell *shell, char *delim, bool *quotes)
{
	char *temp;

	*quotes = false;
	while (*delim)
	{
		if (*delim == '\'' || *delim == '"')
			*quotes = true;
		(*delim)++;
	}
	temp = cleanup_quotes(shell, delim);
	free(delim);
	delim = temp;
	return (delim);
}

static void	run_heredoc(t_shell *shell, int pfd[2], char *delim)
{
	char	*input;
	char	*hd_string;
	bool	quotes;

	delim = new_delim(shell, delim, &quotes);
	rl_clear_history();
	signal(SIGINT, SIG_DFL);
	while (true)
	{
		input = readline("> ");
		if (!input)
			exit(empty_hd_line(pfd, delim));
		if (ft_strcmp(input, delim) == 0)
			break ;
		if (quotes == true)
			hd_string = ft_strdup(input);
		else
			hd_string = check_expansion(shell, input);
		if (!hd_string)
			malloc_fail(shell, "process heredoc line");
		write_w_newline(hd_string, pfd[1]);
		(free(hd_string), free(input));
	}
	(free(input), close(pfd[0]), close(pfd[1]));
	exit(0);
}

static int	setup_heredoc(t_shell *shell, char *delim)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	if (pipe(pfd) == -1)
		exit(1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		run_heredoc(shell, pfd, delim);
	close(pfd[1]);
	ft_wait(shell, pid, &status);
	store_heredoc(pfd[0]);
	signals_init(shell);
	if (WIFSIGNALED(status)
		&& WTERMSIG(status) == SIGINT)
		return (shell->last_errno = 130, -1);
	return (0);
}

int	heredoc(t_shell *shell, char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], "<<", 3) == 0)
		{
			if (setup_heredoc(shell, arr[i + 1]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
