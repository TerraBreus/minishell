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
	sigeof_hd(pfd, delim);
	write_w_newline("", pfd[1]);
	close(pfd[1]);
	return (1);
}

//the final boolean parameter states whether eof has quotes.
//Truncated to 'e' for norminetti spaghetti
static void	run_heredoc(
		t_shell *s, int pfd[2], char *delim, bool *in_quotes)
{
	char	*input;
	char	*hd_string;

	rl_clear_history();
	sig_child();
	while (true)
	{
		input = readline("> ");
		if (!input)
			exit(empty_hd_line(pfd, delim));
		if (ft_strcmp(input, delim) == 0)
			break ;
		if (*in_quotes == true)
			hd_string = ft_strdup(input);
		else
			hd_string = check_expansion(s, input);
		if (!hd_string)
			malloc_fail(s, "process heredoc line");
		write_w_newline(hd_string, pfd[1]);
		free(hd_string);
		free(input);
	}
	free(input);
	close(pfd[1]);
	exit(0);
}

int	setup_heredoc(t_shell *shell, t_redir *r, t_cmd *cmd_list)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	if (pipe(pfd) == -1)
		exit_on_fail(shell, cmd_list, NULL, true);
	pid = fork();
	if (pid == -1)
		exit_on_fail(shell, cmd_list, NULL, true);
	if (pid == 0)
		run_heredoc(shell, pfd, r->filename_path, &r->filename_quotes);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	if (sigint_hd(status) == -1)
		return (close(pfd[0]), -1);
	r->heredoc_fd = pfd[0];
	return (0);
}
