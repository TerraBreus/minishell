/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:34:57 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 17:50:19 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// now you can iterate a list and send extra variables to have them exist in
// the function you apply when iterating
void	ft_lstiter_param(t_list *lst, void (*f)(void *, void *), void *param)
{
	while (lst)
	{
		f(lst->content, param);
		lst = lst->next;
	}
}
