/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:06:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO, make error code
void	syntax_error(char *message)
{
	printf("bash: ");
	if (!message)
		printf("unknown error\n");
	printf("%s\n", message);
}

// cleans up and exits program
// message auto-satrt with "malloc fail "
void	malloc_fail(char *message, t_custom_env	*my_env, t_list *token_list)
{
	if (my_env)
		cleanup_env(my_env);
	if (token_list)
		ft_lstclear(&token_list, token_del);
	printf("bash: malloc failed ");
	if (!message)
		printf("unknown error\n");
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
