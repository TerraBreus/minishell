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

#ifndef	STRUCTS_H
# define STRUCTS_H

typedef struct			s_token_data
{
	char				*token;
	bool				in_singles;
	bool				in_doubles;
}						t_token_data;

#endif