/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:41:30 by artblin           #+#    #+#             */
/*   Updated: 2022/04/27 19:07:46 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*str_join(const char *left, const char *right)
{
	char	*o;
	char	*merge;

	if (left && right)
	{
		const int len = get_len(left) + get_len(right);
		if (xmalloc(&merge, len + 1, TMP_ALLOC))
			return (NULL);
		o = merge;
		while (*left)
			*(merge)++ = *(left)++;
		while (*right)
			*(merge)++ = *(right)++;
		*merge = '\0';
		return (o);
	}
	return (NULL);
}
