/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:56:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/26 20:09:16 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_str
{
	char			*str;
	int				len;
}	t_str;

typedef struct s_hst
{
	t_str			cmd;
	struct s_hst	*next;
	struct s_hst	*prev;
}	t_hst;

typedef struct s_env
{
	t_str			key;
	t_str			value;
	struct s_env	*next;
}	t_env;

typedef struct s_ctx
{
	int				fd_history;
	t_hst			*history;
	t_env			*env;
	t_env			*var;
}	t_ctx;

#endif
