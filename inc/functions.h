/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:05 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:48:06 by masmit           ###   ########.fr       */
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
void			malloc_fail(char *message, t_custom_env	*my_env);

// some tokens are operators, eg pipe, redirect or append
t_token_type	get_operator_type(char *token);
void			token_del(void *content);

// leftover utilities for small functions and debugging.
void			print_tokens(t_list *head);
bool			is_operator(char c);

// custom env init
t_custom_env	*shell_env_init(char **env);
void			cleanup_env(t_custom_env *my_env);

// custom env commands
void			my_export(t_custom_env *my_env, char *new_var, char *value);
void			my_unset(t_custom_env *my_env, char *variable);
char			*my_getenv(t_custom_env *my_env, char *variable);

#endif