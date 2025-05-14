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

// global signal declared in included_libs, otherwise makefile error
void	env_init(t_shell *shell, char **env);
void	local_init(t_shell *shell);

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
void	my_export(t_shell *shell, char *arg);
void	export_local(t_shell *shell, char *variable);
bool	print_export_list(t_shell *shell, char **env_copy);

// pass tokens to parser
void	token_to_struct(t_shell *shell, t_cmd **exec);
void	add_redir(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);
void	add_args(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);
void	print_exec(t_cmd *exec);

// utils bools
bool	has_path(char *str);
bool	is_path(char *str, size_t *i);
bool	is_operator(char c);
bool	is_input_empty(t_shell *shell, char *input);
bool	is_quote(char c);
void	update_bools(
			char c, bool *in_singles, bool *in_doubles);

// signals
void	setup_signals(void);
void	signal_is_int(t_shell *shell);
void	ctrl_d(char *input);

// utils else
void	skip_litteral(char *str, size_t *i);
void	skip_space(char *input, size_t *i);
void	print_tokens(t_shell *shell);
void	just_print(char **temp_arr);

// no leaks
void	cleanup_shell(t_shell *shell);

// in case of errors
void	malloc_fail(t_shell *shell, char *location);
void	syntax_error(t_shell *shell, char *invalid_token);

#endif