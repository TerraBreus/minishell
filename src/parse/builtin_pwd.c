/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   And all the pieces matter...                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Me                                         +#+  +:+       +#+        */
/*       Shoutout to: Terry A. Davis              +#+#+#+#+#+   +#+           */
/*   Created: / 66:77:88 by The Chosen One             #+#    #+#             */
/*   Updated: / 66:77:88 by Me                        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pwd(t_shell *shell)
{
	char	*location;

	location = malloc(PATH_MAX);
	if (!location)
	{
		malloc_fail(shell, "my pwd");
		return ;
	}
	if (getcwd(location, PATH_MAX) != NULL)
		printf("%s\n", location);
	else
		printf("PWD couldn't be determined\n");
	free(location);
}
