/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:38:45 by masmit            #+#    #+#             */
/*   Updated: 2024/11/01 17:51:53 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst check must be or not and
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || (!f || !del))
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (new_list == NULL)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

// void	print_list(t_list *head) {
// 	t_list *current;
// 	current = head;
// 	while (current != NULL) {
// 		printf("content at node = %d\n", *(int*)current->content);
// 		current = current->next;
// 	}
// 	printf("all content at list has been shown.\n");
// }

// int	*add_10(void *content)
// {
// 	int *new_value;

// 	new_value = malloc(sizeof(int));
// 	if (!new_value)
// 		return (NULL);
// 	*new_value = (*(int *)content) + 10;
// 	return (new_value);
// }

// void delete_all(void *content)
// {
// 	free(content);
// 	return ;
// }

// int	main(void)
// {
// 	t_list *head;
// 	t_list *temp;
// 	t_list *new_list;
// 	t_list	*current;
// 	int value;
// 	int count;
// 	void (*f)(int);
// 	void (*del)(void *);
// 	f = (void *)add_10;
// 	del = (void *)delete_all;

// 	head = NULL;
// 	value = 1;
// 	count = 0;
// 	while (count < 5)
// 	{
// 		int *i = malloc(sizeof(int));
// 		if (i == NULL)
// 			return (0);
// 		*i = value;
// 		temp = ft_lstnew(i);
// 		if (head == NULL)
// 		{
// 			head = temp;
// 		}
// 		else
// 		{
// 			current = head;
// 			while (current->next != NULL)
// 				current = current->next;
// 			current->next = temp;
// 		}
// 		//free(i);
// 		value++;
// 		count++;
// 	}
// 	print_list(head);
// 	new_list = ft_lstmap(head, (void *)f, del);
// 	if (!new_list)
// 		return (0);
// 	print_list(new_list);
// }

// not my function
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new;
// 	t_list	*head;

// 	if (!lst && (!f || !del))
// 		return (NULL);
// 	head = ft_lstnew(f(lst->content));
// 	if (head == NULL)
// 	{
// 		return (NULL);
// 	}
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		new = ft_lstnew(f(lst->content));
// 		if (new == NULL)
// 		{
// 			ft_lstclear(&head, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&head, new);
// 		lst = lst->next;
// 	}
// 	return (head);
// }
