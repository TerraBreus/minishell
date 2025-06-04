/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:05 by masmit            #+#    #+#             */
/*   Updated: 2025/06/04 13:59:53 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// global signal declared in included_libs, otherwise makefile error
int		shell_init(t_shell *shell);

void	loop(t_shell *shell);

// prompt to tokens
void	tokenize_input(t_shell *shell, char *input);
void	token_len(t_shell *shell, char *input, size_t *i);
void	token_quote(t_shell *shell, char *input, size_t *i);

// once tokenized
void	expand_tokens(t_shell *shell);

// also used by heredoc
char	*check_expansion(t_shell *shell, char *str);

// remove outside most quotes
char	*cleanup_quotes(t_shell *shell, char *token);

// pass tokens to parser
void	token_to_struct(t_shell *shell, t_cmd **exec);
void	add_redir(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);
void	add_args(t_shell *shell, t_cmd *cmd, char **tokens, size_t *i);

// and cleanup after
void	cleanup_struct(t_cmd **exec);
void	print_exec(t_cmd *exec);

// builtins
int		my_echo(char **arg_array);
int		my_env(t_shell *shell);
int		my_cd(t_shell *shell, char **arg_list);
int		my_export(t_shell *shell, char **arg_list);
int		my_unset(t_shell *shell, char **arg_list);
int		my_pwd(t_shell *shell);

// builtin helper
void	remove_arg(char **env, size_t *delete_pos);
void	add_to_env(t_shell *shell, char *str);
int		find_index(char **env_array, char *str, size_t len);
char	*my_getenv(t_shell *shell, char *var_name);

// utils bools
bool	has_path(char *str);
bool	is_path(char *str, size_t *i);
bool	is_operator(char c);
bool	is_input_empty(t_shell *shell, char *input);
bool	is_quote(char c);
void	update_bools(
			char c, bool *in_singles, bool *in_doubles);

// hd = heredoc
// signals
int		signals_init(t_shell *shell);
void	sigint(t_shell *shell);
void	sigquit(t_shell *shell, char *input);
void	sig_child(void);
int		sigint_hd(int status);
void	sigeof_hd(int pfd[2], char *delim);
void	sigint_parent(t_shell *shell_data, pid_t pid);

// utils else
void	skip_litteral(char *str, size_t *i);
void	skip_blank(char *input, size_t *i);
void	print_tokens(t_shell *shell);
void	just_print(char **temp_arr);

// no leaks
void	cleanup_shell(t_shell *shell);
void	cleanup_env(t_shell *shell);

// in case of errors
void	quick_clean(t_shell *shell);
void	malloc_fail(t_shell *shell, char *location);
void	syntax_error(t_shell *shell, char *invalid_token);
void	sigaction_fail(t_shell *shell, int error);
void	subject_error(t_shell *shell, char c);

// temp for checking builtins
int		builtin(t_shell *shell, t_cmd **exec);

// -------------------------------
// EXECUTION (unsorted)
// --------------------------------

void	execution(t_cmd *cmd_list, t_shell *shell_data);

//	Simple functions counting amount of commands to execute
int		count_commands(t_cmd *cmd_list);

//On SAVE, function duplicates the STDIN STDOUT processes
// and saves it in static variables.
//On RESTORE, function closes the files attached to STDIN
// and STDOUT FILENO and dupes them to the copies
//(making interaction for a new prompt possible)
//On CLOSE, which is more for the child processes.
// the copies of STDIN and STDOUT are closed.
int		save_close_restore_io(int save_close_restore);

// FUNCTIONS USED ONLY WHEN PIPING
int		mult_cmd(t_cmd *cmd_list, t_shell *shell_data);
void	parse_mult_cmd(t_cmd *cmd_list);

// pipe pointer can be set to NULL if no pipe is needed (aka single_command)
int		builtout_cmd(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data);

//simple pipe call but in a struct.
int		create_pipe(t_pipe *pipe_data);

//Function dup2's to stdin/out and closes pipes for both child as the parent
int		setup_pipe_builtout(t_pipe *pipe_data, pid_t pid, t_cmd_type type);

//setup_redirections
int		setup_redir(t_redir *redir_data);

//redirection_handlers.c
int		handle_in(t_redir *r);
int		handle_out(t_redir *r);
int		handle_append(t_redir *r);
int		handle_heredoc(t_redir *r);

// Executing a single (built out) command using execve.
int		exec_cmd(char **cmd_and_flags, char **envp);

//simple strncmp to check if command is built_in or not.
bool	is_built_in(t_cmd *cmd_list);

//sets up pipe for builtin command (without forking)
int		setup_pipe_builtin(t_pipe *pipe_data, t_cmd_type type);
// overal flow for builtin_command
int		builtin_cmd(t_shell *shell, t_cmd *exec, t_pipe *pipe_data);
//function for when prompt only asks for a single command (build in or out)
int		single_cmd(t_cmd *cmd_list, t_shell *shell_data);

//function iterates through cmd_list and its corresponding redirection
// list, checks for heredoc types and calls setup_heredoc
int		check_4_heredoc(t_shell *shell, t_cmd *cmd_list);
int		setup_heredoc(t_shell *shell, t_redir *r);
#endif
