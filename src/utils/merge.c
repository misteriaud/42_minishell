/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:41:30 by artblin           #+#    #+#             */
/*   Updated: 2022/03/28 15:56:25 by artblin          ###   ########.fr       */
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

t_err	merge(t_str *merged, t_str *left, t_str *right, const char sep)
{
	int	const	len = left->len + right->len + !!(sep);
	int			x;
	int			z;

	x = 0;
	if (!left->str | !right->str)
		return (NULL_PTR_ERROR);
	if (xmalloc(&(merged->str), len + 1, TMP_ALLOC))
		return (MEMORY_ERROR);
	merged->str[len] = '\0';
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
