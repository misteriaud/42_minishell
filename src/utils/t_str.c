/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:18:54 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 22:19:08 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	new_str(t_str *data, const int len, const int alloc_group)
{
	if (xmalloc(&(data->str), len + 1, alloc_group))
		return (MEMORY_ERROR);
	data->len = len;
	return (NO_ERROR);
}
