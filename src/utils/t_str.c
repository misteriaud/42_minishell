/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:18:54 by artblin           #+#    #+#             */
/*   Updated: 2022/05/19 11:10:22 by mriaud           ###   ########.fr       */
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

t_err	str_dup(char **new, const char *str, int alloc)
{
	size_t	x;

	x = get_len(str);
	if (xmalloc(new, sizeof(char) * ++x, alloc))
		return (MEMORY_ERROR);
	if (!str)
		return (NO_ERROR);
	while (*str)
		*(*new)++ = *(str)++;
	*new -= (--x);
	return (NO_ERROR);
}
