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

#endif