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
char			*get_token(char *input, size_t *i);
char			*quote_token(char *input, size_t *i);
char 			*expand_var(char *input, size_t *i);

// checks if tokens are valid, and give error accordingly
void			syntax_error(char *message);

// some tokens are operators, eg pipe, redirect or append
t_token_type	get_operator_type(char *token);
void			token_del(void *content);

// leftover utilities for small functions and debugging.
void			print_tokens(t_list *head);
bool			is_operator(char c);

#endif