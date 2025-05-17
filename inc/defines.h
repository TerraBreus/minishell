/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:00 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:48:01 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define FAILURE false
# define SUCCES true

# define SYNTAX_ERROR 2

// -- READABILITY VARIABLES -- 
# define RESTORE 0
# define SAVE 1
# define CLOSE 2

// typdef of point to function.
typedef int (*t_redir_handler)(t_redir *r);

#endif
