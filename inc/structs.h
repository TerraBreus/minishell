/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                           :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:18 by masmit            #+#    #+#             */
/*   Updated: 2025/05/01 16:01:02 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_custom_env {
  char **env_copy;
} t_custom_env;

typedef enum e_token_type {
  TOKEN_WORD,
  TOKEN_WORD_WITH_PATH,
  TOKEN_PIPE,
  TOKEN_REDIRECT_IN,
  TOKEN_REDIRECT_OUT,
  TOKEN_APPEND,
  TOKEN_HEREDOC,
  TOKEN_EOF
} t_token_type;

typedef struct s_token_data {
  char *token;
  t_token_type type;
  char *error;
} t_token_data;

// --Structs for executing commands, piping,--
// --heredoc and other redirection operators--

typedef enum e_redir_type
{
	IN,
	APPEND,
	OUT,
	HEREDOC 
} t_redir_type;

typedef struct s_redir {
  int heredoc_fd;
  t_redir_type type;
  char *filename_path;
  struct s_redir *next;
} t_redir;

typedef struct s_cmd {
  char **argv;
  t_redir *redirection;
  pid_t pid;
  struct s_cmd *next;
} t_cmd;

#endif
