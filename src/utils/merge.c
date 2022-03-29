/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:41:30 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 16:50:17 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len(const char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

t_err	new_str(t_str *data, const int len, const int alloc_group)
{
	if (xmalloc(&(data->str), len + 1, alloc_group))
		return (MEMORY_ERROR);
	data->len = len;
	return (NO_ERROR);
}

t_err	str_fill(t_str *dst, const char *str)
{
	int		x;

	x = 0;
	if (!dst->len)
		return (NO_BYTE_ERROR);
	while (x < dst->len)
	{
		dst->str[x] = str[x];
		x++;
	}
	return (NO_ERROR);
}

t_err	merge(t_str *merged, t_str *left, t_str *right, const char sep)
{
	int	const	len = left->len + right->len + !!(sep);
	int			x;
	int			z;

	x = 0;
	if (!merged->str | !left->str | !right->str)
		return (NULL_PTR_ERROR);
	z = 0;
	while (z < left->len)
		merged->str[x++] = left->str[z++];
	if (sep)
		merged->str[x++] = sep;
	z = 0;
	while (z < right->len)
		merged->str[x++] = right->str[z++];
	merged->len = len;
	return (NO_ERROR);
}
