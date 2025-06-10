/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   internal_error.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: zivanov <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/10 09:47:08 by zivanov        #+#    #+#                */
/*   Updated: 2025/06/10 09:47:10 by zivanov        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	internal_error(void)
{
	perror("Internal error occured.");
	return (INTERNAL_ERROR);
}
