/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:39:32 by masmit            #+#    #+#             */
/*   Updated: 2024/10/15 15:28:55 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	valid_filename(char c)
{
	if (!c)
		return (false);
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}
