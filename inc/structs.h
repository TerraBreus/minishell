/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:18 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:48:19 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_custom_env
{
	char			**env_copy;
}					t_custom_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_WORD_WITH_PATH,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token_data
{
	char			*token;
	t_token_type	type;
	char			*error;
}					t_token_data;

#endif