/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:00 by masmit            #+#    #+#             */
/*   Updated: 2025/05/16 18:36:45 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define FAILURE false
# define SUCCES true

# define SYNTAX_ERROR 2

# define EXPORT_ERROR "\
minishell: export: invalid identifier found in filename\n"

# define OPERATOR_ERROR "\
unknown operator combination"

#endif