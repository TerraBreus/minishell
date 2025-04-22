/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:54:58 by masmit            #+#    #+#             */
/*   Updated: 2024/10/29 16:49:06 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// go to last node in list and add content
void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*tmp;

	if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp -> next = node;
}
