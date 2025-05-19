/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: terrabuntu <terrabuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:05 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 16:27:49 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

// identifieng input into tokens.
t_list			*tokenize_input(char *input);
char			*token_get(char *input, size_t *i);
char			*token_quote(char *input, size_t *i);
char			*token_heredoc(char *input, size_t *i);

// checks if tokens are valid, and give error accordingly
void			syntax_error(char *message);
void			malloc_fail(
					char *message, t_custom_env	*my_env, t_list *token_list);

// once tokenized, iterate through token, label and expand them
void			token_expansion(t_list *token_list, t_custom_env *env);
char			*insert_path(char *token, t_custom_env *env);

// iteration helper functions
void			token_del(void *content);

// put tokens in new cmd struct for exec
t_cmd			*cmd_struct(t_list *token_list);
void			print_cmd_list(t_cmd *cmd_list);
void			cleanup_cmd_list(t_cmd *cmd_head);

// utils for building the struct
void			copy_argv(char **new_argv, char **old_argv, int argc);
void			append_redir(t_cmd *cmd, t_redir *redir);
t_redir_type	get_redir_type(t_token_type type);

// leftover utilities for small functions and debugging.
void			print_tokens(t_list *head);
bool			is_operator(char c);
void			skip_litteral(char *token, size_t *i);

// custom env init
t_custom_env	*shell_env_init(char **env);
void			cleanup_env(t_custom_env *my_env);

// custom env commands
void			my_export(t_custom_env *my_env, char *new_var, char *value);
void			my_unset(t_custom_env *my_env, char *variable);
char			*my_getenv(t_custom_env *my_env, char *variable);

/*
// - - - - - - - - - - - - - - - - - - - - - - \\
// --oxO--  E  X  E  C  U  T  I  O  N  --Oxo-- \\
// - - - - - - - - - - - - - - - - - - - - - - \\
*/

//adult_entertainment.c
int	adult_entertainment(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *pipe_data);

//child_slavery.c
void	child_slavery(t_cmd *cmd_list, t_custom_env *t_envp, t_pipe *plumb_box);

//count_commands.c
int	count_commands(t_cmd *c);

//execute_command.c
int	exec_cmd(char **cmd_and_flags, char **envp);

//find_executables.c
char	*find_full_path(char *paths[], char *cmd);
char	**create_possible_paths(char *envp[]);
void	free_paths(char **possible_paths);

//init_pipe_struct.c
int	init_pipe(t_pipe **plumb_box);

//main_execution.c
int	chain_of_commands(t_cmd *cmd_list, t_custom_env *t_envp);

//multiple_commands.c
int	multiple_commands(t_cmd *cmd_list, t_custom_env *t_envp);

//redirection_handlers.c
int	handle_in(t_redir *r);
int	handle_out(t_redir *r);
int	handle_append(t_redir *r);
int	handle_heredoc(t_redir *r);

//pipe handling.
int	setup_pipe_last_cmd(t_pipe *pipe_data);
int	setup_pipe_middle_cmd(t_pipe *pipe_data);
int	setup_pipe_first_cmd(t_pipe *pipe_data);

//restore_io.c
int	save_or_restore_io(int restore_or_save);

//set_redirection.c
int	set_redirection(t_redir *redir_data);

//setup_lastreadend.c
int	set_last_read_end(t_pipe *p);

//single_command.c;
int	single_command(t_cmd *cmd_list, t_custom_env *t_envp);

//temp_single_command.c (This is here cause I need to clone stuff BEFORE executing single_command
int	temp_single_command(t_cmd *cmd_list, t_custom_env *envp);

#endif
