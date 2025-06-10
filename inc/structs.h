/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:18 by masmit            #+#    #+#             */
/*   Updated: 2025/05/21 15:31:41 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// tc = token count
typedef struct e_shell
{
	char			**tokens;
	size_t			tc;
	char			**env;
	char			**export;
	char			*old_pwd;
	int				last_errno;
	bool			found_error;
}					t_shell;

typedef enum e_type
{
	IN,
	APPEND,
	OUT,
	HEREDOC,
	NONE
}	t_type;

typedef struct s_redir
{
	int				heredoc_fd;
	char			*heredoc_delimiter;
	char			*filename_path;
	bool			filename_quotes;
	t_type			type;
	struct s_redir	*next;
}					t_redir;

typedef int	(*t_redir_handler)(t_redir *r);

typedef enum e_cmd_type
{
	FIRST,
	MIDDLE,
	LAST,
	SINGLE
}	t_cmd_type;

typedef struct s_cmd
{
	char			**argv;
	pid_t			pid;
	t_redir			*redirection;
	struct s_cmd	*next;
	t_cmd_type		type;
	bool			built_in;
}					t_cmd;

typedef struct s_pipe
{
	int	pfd[2];
	int	lre;
}	t_pipe;

#endif
