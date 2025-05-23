/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:05 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 15:18:10 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// global signal declared in included_libs, otherwise makefile error
int		env_init(t_shell *shell);

void	loop(t_shell *shell);

// prompt to tokens
void	token_quote(t_shell *shell, char *input, size_t *i);
void	token_operator(t_shell *shell, char *input, size_t *i);
void	tokenize_input_len(t_shell *shell, char *input, size_t *i);

// once tokenized
void	expand_tokens(t_shell *shell);

// void	cleanup_quotes(t_shell *shell);
char	*cleanup_quotes(t_shell *shell, char *token);

// env cmd_list
char	*my_getenv(t_shell *shell, char *var_name);

// pass tokens to parser
void	token_to_struct(t_shell *shell, t_cmd **exec);
void	add_redir(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);
void	add_args(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);

// and cleanup after
void	cleanup_struct(t_cmd **exec);
void	print_exec(t_cmd *exec);

// exec single command
void	exec_single(t_shell *shell, t_cmd **exec);

// builtins
void	my_echo(char **arg_array);
void	my_env(t_shell *shell);
void	my_cd(t_shell *shell, char **arg_list);
void	my_export(t_shell *shell, char **arg_list);
void	my_unset(t_shell *shell, char **arg_list);
void	my_pwd(t_shell *shell);

// builtin helper
void	remove_arg(char **env_copy, size_t *delete_pos);
void	add_to_env(t_shell *shell, char *str);
int		find_index(char **env_array, char *str, size_t len);

// utils bools
bool	has_path(char *str);
bool	is_path(char *str, size_t *i);
bool	is_operator(char c);
bool	is_input_empty(t_shell *shell, char *input);
bool	is_quote(char c);
void	update_bools(
			char c, bool *in_singles, bool *in_doubles);

// signals
void	setup_signals(t_shell *shell);
void	sigint(t_shell *shell);
void	sigquit(char *input);

// utils else
void	skip_litteral(char *str, size_t *i);
void	skip_space(char *input, size_t *i);
void	print_tokens(t_shell *shell);
void	just_print(char **temp_arr);

// no leaks
void	cleanup_shell(t_shell *shell);
void	cleanup_env(t_shell *shell);

// in case of errors
void	malloc_fail(t_shell *shell, char *location);
void	syntax_error(t_shell *shell, char *invalid_token);
void	sigaction_fail(t_shell *shell, int error);

// -------------------------------
// EXECUTION (unsorted)
// --------------------------------

void	execution(t_cmd *cmd_list, t_shell *shell_data);

//	Simple functions counting amount of commands to execute
int	count_commands(t_cmd *cmd_list);

//On SAVE, function duplicates the STDIN STDOUT processes and saves it in static variables.
//On RESTORE, function closes the files attached to STDIN and STDOUT FILENO and dupes them to the copies
//(making interaction for a new prompt possible)
//On CLOSE, which is more for the child processes. the copies of STDIN and STDOUT are closed.
int	save_close_restore_io(int save_close_restore);

// FUNCTIONS USED ONLY WHEN PIPING
int	mult_cmd(t_cmd *cmd_list, t_shell *shell_data);
void	parse_mult_cmd(t_cmd *cmd_list);

// pipe pointer can be set to NULL if no pipe is needed (aka single_command)
int	builtout_cmd(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data);

//simple pipe call but in a struct.
int	create_pipe(t_pipe *pipe_data);

//Function dup2's to stdin/out and closes pipes for both child as the parent
int	setup_pipe_builtout(t_pipe *pipe_data, pid_t pid, t_cmd_type type);

//setup_redirections
int	setup_redir(t_redir *redir_data);

//redirection_handlers.c
int	handle_in(t_redir *r);
int	handle_out(t_redir *r);
int	handle_append(t_redir *r);
int	handle_heredoc(t_redir *r);

// Executing a single command using execve.
int	exec_cmd(char **cmd_and_flags, char **envp);

#endif
