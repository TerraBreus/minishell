/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:52:31 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_delimiter(char *input, size_t *i)
{
	size_t	start;
	char	quote;

	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[*i];
		(*i)++;
		start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (!input[*i])
			return (syntax_error("unclosed quotes as heredoc delimiter"), NULL);
		return (ft_substr(input, start - 1, *i - start + 2));
	}
	else
	{
		while (input[*i]
			&& !is_space(input[*i])
			&& !is_operator(input[*i]))
			(*i)++;
		return (ft_substr(input, start, *i - start));
	}
	return (NULL);
}

static char	*heredoc_readline(char *line, char *delimiter)
{
	line = readline("> ");
	if (!line)
	{
		printf("minishell: warning: here-document delimited by end-of-file\n");
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*token_heredoc(char *input, size_t *i)
{
	char	*heredoc_content;
	char	*delimiter;
	char	*line;
	char	*temp;

	while (is_space(input[*i]))
		(*i)++;
	delimiter = heredoc_delimiter(input, i);
	if (!delimiter)
		return (malloc_fail("delimiter in heredoc", NULL), NULL);
	heredoc_content = ft_strdup("");
	while (true)
	{
		line = heredoc_readline(line, delimiter);
		if (!line)
			break ;
		temp = strjoin_and_free(heredoc_content, line);
		heredoc_content = ft_strjoin(temp, "\n");
		free(temp);
		if (!heredoc_content)
			return (malloc_fail("strjoin in heredoc", NULL), NULL);
	}
	free(delimiter);
	return (heredoc_content);
}
