/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:41:30 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 22:19:10 by artblin          ###   ########.fr       */
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
