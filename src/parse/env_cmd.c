/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:55 by masmit            #+#    #+#             */
/*   Updated: 2025/05/05 14:14:58 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// my_unset()
// {

// }

// bool	is_valid_arg(char *arg, size_t *i)
// {
// 	if (arg[0] != '_' || !ft_isalpha(arg[0]))
// 		return (FALSE);
// 	i++;
// 	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
// 		(*i)++;
// 	if (arg[*i] != '=')
// 		return (FALSE);
// 	return (TRUE);
// }

// // just pass arg with '=' inside, ill do the rest
// // on no next arg export behaves differently, also handled
// int	my_export(t_shell *shell, char *arg)
// {
// 	size_t	i;
// 	size_t	name_len;
// 	char	*name;

// 	i = 0;
// 	name_len = 0;
// 	if (!arg)
// 		print_export();
// 	if (is_valid_arg(arg, &name_len) == FALSE)
// 		return (FAILURE);
// 	name = ft_substr(arg, 0, name_len);
// 	if (!name)
// 		return (malloc_fail(shell, "my export"), FAILURE);
// 	while (ft_strncmp(shell->env_copy[i], name, name_len) != 0)
// 		i++;
// 	shell->env_copy = ft_realloc(shell->env_copy,
// 							sizeof(char *) * i,
// 							(sizeof(char *) * i) + 2);
// 	if (!shell->env_copy)
// 		return (malloc_fail(shell, "my export"), FAILURE);
// 		return (FAILURE);
// 	return (SUCCES);
// }

void	my_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env_copy[i])
	{
		write(STDOUT_FILENO, shell->env_copy[i], ft_strlen(shell->env_copy[i]));
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

char	*my_getenv(t_shell *shell, char *var_name)
{
	size_t	var_name_len;
	size_t	env_items;
	size_t	i;

	if (!var_name)
		return (NULL);
	env_items = 0;
	i = 0;
	var_name_len = ft_strlen(var_name);
	while (shell->env_copy[env_items])
	{
		if (ft_strncmp(shell->env_copy[env_items],
				var_name, var_name_len) == 0)
		{
			while (shell->env_copy[env_items][i] != '=')
				i++;
			return (ft_substr(shell->env_copy[env_items], i + 1,
					ft_strlen(shell->env_copy[env_items]) - i));
		}
		env_items++;
	}
	return (NULL);
}
