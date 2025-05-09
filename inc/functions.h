/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:05 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 16:53:19 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

void	env_init(t_shell *shell);

void	loop(t_shell *shell);

// prompt to tokens
void	token_quote(t_shell *shell, char *input, size_t *i);
void	token_operator(t_shell *shell, char *input, size_t *i);
void	tokenize_input_len(t_shell *shell, char *input, size_t *i);

// once tokenized
void	expand_tokens(t_shell *shell);
void	cleanup_quotes(t_shell *shell);

// env cmd_list
char	*my_getenv(t_shell *shell, char *var_name);

// pass tokens to parser
void	token_to_struct(t_shell *shell, t_cmd **exec);
void	add_redir(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);
void	add_args(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);
void	print_exec(t_cmd *exec);

// utils bools
bool	has_path(char *str);
bool	is_path(char *str, size_t *i);
bool	is_operator(char c);

// utils else
void	skip_litteral(char *str, size_t *i);
void	skip_space(char *input, size_t *i);
void	print_tokens(t_shell *shell);

// no leaks
void	cleanup_shell(t_shell *shell);

void	malloc_fail(t_shell *shell, char *location);
void	syntax_error(t_shell *shell, char *invalid_token);

#endif