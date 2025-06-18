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
	char	*temp;

	*quotes = false;
	if (ft_strchr(delim, '\'') || ft_strchr(delim, '\"'))
	{
		*quotes = true;
		temp = cleanup_quotes(shell, delim);
		free(delim);
		delim = temp;
	}
	return (delim);
}

void	run_heredoc(t_shell *shell, int pfd[2], char *delim)
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
