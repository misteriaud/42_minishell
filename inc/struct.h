/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:56:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/25 19:56:34 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_str
{
	char	*str;
	int		len;
}	t_str;

typedef struct s_ctx
{
	int		fd_history;
	t_str	*head_history;
}	t_ctx;
