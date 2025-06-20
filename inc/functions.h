/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:05 by masmit            #+#    #+#             */
/*   Updated: 2025/06/18 17:54:18 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// global signal declared in included_libs, otherwise makefile error
int		shell_init(t_shell *shell);

void	loop(t_shell *shell);

// prompt to tokens
void	tokenize(t_shell *shell, char *input);
void	token_len(t_shell *shell, char *input, size_t *i);

// syntax check
void	syntax_check(t_shell *shell);
void	ambiguous_check(t_shell *shell, char **arr);
t_type	redir_type(char *token);

// once tokenized
void	rm_empty(t_shell *shell);

// also used by heredoc
char	*check_expansion(t_shell *shell, char *str);

// remove outside most quotes
char	*cleanup_quotes(t_shell *shell, char *token);

// pass tokens to parser
void	token_to_struct(t_shell *shell, char **arr, t_cmd **exec);
void	add_cmd_back(t_cmd **exec, t_cmd *new_cmd);
t_cmd	*new_node(t_shell *shell);

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

// utils else
void	skip_litteral(char *str, size_t *i);
void	skip_blank(char *input, size_t *i);
void	print_tokens(t_shell *shell);
void	just_print(char **temp_arr);
void	free_arr(char **arr);

// no leaks
void	cleanup_shell(t_shell *shell);
void	cleanup_env(t_shell *shell);
void	cleanup_struct(t_cmd **exec);

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

//function forks from parent and sets up signals 
//and redirection for the child process to be executed.
int		builtout_cmd(t_cmd *cmd_list, t_shell *shell_data);

//simple pipe call but in a struct.
int		create_pipe(t_pipe *pipe_data);

//Functions that help find the path for a command
//from the different paths directions in the environment variable
char	*find_full_path(char *paths[], char *cmd);
char	**create_possible_paths(char *envp[]);
void	free_paths(char **possible_paths);
bool	relative_path(char *path);

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
// functions also parses for filepath of executable
int		exec_cmd(char **cmd_and_flags, char **envp);

//simple strncmp to check if command is built_in or not.
bool	is_built_in(t_cmd *cmd_list);

// overal flow for builtin_command; sets up redirection
// and then calls builtin(); 
int		builtin_cmd(t_shell *shell, t_cmd *exec);
//function for when prompt only asks for a single command (build in or out)
int		single_cmd(t_cmd *cmd_list, t_shell *shell_data);

//function iterates through cmd_list and its corresponding redirection
// list, checks for heredoc types and calls setup_heredoc
// int		check_4_heredoc(t_shell *shell, t_cmd *cmd_list); // now redundent!
// int		setup_heredoc(t_shell *shell, t_redir *r, t_cmd *cmd_list);
// int		setup_heredoc(t_shell *shell, char *delim); // now redundent!
int		heredoc(t_shell *shell, char **arr);
void	run_heredoc(t_shell *shell, int pfd[2], char *delim);

//Wait call to retrieve exit status of child.
int		ft_wait(t_shell *shell, int last_pid, int *status);

//Checks for file permissions based on the type of redirection.
// Returns -1 if insufficient permissions.
//or if incorrect type is given (which means the function is called in a place
//where it makes no sense to call it)
int		check_file_permissions(char *filename, t_type type);

//new function for mult_cmd that will fork and execute
int		child_command(t_cmd *cmd_list, t_shell *shell_data, t_pipe *pipe_data);

// failure and clean up calls
void	exit_on_fail(t_shell *shell, t_cmd *cmd_list,
			t_pipe *pipe_data, bool p_error);
void	close_pipe(t_pipe *pipe_data);
int		store_heredoc(int pipe_read);	
void	close_heredoc_parent(t_redir *r);

#endif
