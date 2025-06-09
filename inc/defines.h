/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:00 by masmit            #+#    #+#             */
/*   Updated: 2025/06/07 16:13:54 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define FAILURE		false
# define SUCCESS		true

# define SYNTAX_ERROR	2
# define DIR_PROMPT		126
# define DIR_NOT_FOUND	127
# define DIR_UPDATED	0
# define DIR_N_UPDATED	1

# define EXPORT_ERROR	"\
minishell: export: invalid identifier found in filename\n"

# define OPERATOR_ERROR	"\
unknown operator combination"

# define CWD_ERROR "\
WARNING: unable to get current working directory\n"

# define PWD_ERROR "\
WARNING: unable to go to given directory\n"

# define CD_TOO_MANY_ARGS "\
minishell: cd: too many arguments\n"

# define UNKNOWN_PWD "\
PWD couldn't be determined\n"

# define EOF_ERROR "\
minishell: warning: here-document delimited by end-of-file wanted `"

# define EXIT_ERR "\
minishell: exit: too many arguments\n"

# define BUILTIN_NOT_FOUND -1

# define SAVE		0
# define RESTORE	1
# define CLOSE		2

#define INTERNAL_ERROR -1337
#endif
