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
# define STRUCTS_H

// tc = token count
typedef struct e_shell
{
	char			**tokens;
	size_t			tc;
	char			**env_copy;
	char			**exp_copy;
	char			*old_pwd;
	int				last_errno;
	bool			found_error;
}					t_shell;

// --Structs for executing commands, piping,--
// --heredoc and other redirection operators--

typedef enum e_redir_type
{
	IN,
	APPEND,
	OUT,
	HEREDOC,
	NONE
}	t_redir_type;

typedef struct s_redir
{
	int				heredoc_fd;
	char			*filename_path;
	t_redir_type	type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	pid_t			pid;
	t_redir			*redirection;
	struct s_cmd	*next;
}					t_cmd;

#endif
