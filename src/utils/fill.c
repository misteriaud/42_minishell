/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:18:10 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 15:39:07 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

t_err	str_fill_from_lst(t_str *out, t_lst *lst)
{
	int		x;

	if (!lst | !out | !out->str)
		return (NULL_PTR_ERROR);
	x = 0;
	while (lst)
	{
		if (lst->data.str)
		{
			while (*(lst->data.str))
				out->str[x++] = *(lst->data.str)++;
		}
		lst = lst->next;
	}
	return (NO_ERROR);
}
