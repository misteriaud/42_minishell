/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:43:33 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 15:26:27 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	split_lst_normal(t_lst **head, const char *str,
		const char sep, const int alloc_group)
{
	t_lst	**elm;
	int		byte;

	*head = NULL;
	elm = head;
	while (*str)
	{
		while (*str == sep)
			++str;
		if (byte_count(str, &byte, sep))
			break ;
		if (xmalloc(elm, sizeof(t_lst), alloc_group)
			| xmalloc(&((*elm)->data.str), (byte + 1), alloc_group))
			return (MEMORY_ERROR);
		(*elm)->data.len = byte;
		byte = 0;
		while (*str && *str != sep)
			(*elm)->data.str[byte++] = *(str)++;
		elm = &((*elm)->next);
	}
	return (NO_ERROR);
}

t_err	split_lst_inverted(t_lst **head, const char *str,
		const char sep, const int alloc_group)
{
	t_lst	*elm;
	int		byte;

	*head = NULL;
	while (*str)
	{
		while (*str == sep)
			++str;
		if (byte_count(str, &byte, sep))
			break ;
		if (xmalloc(&elm, sizeof(t_lst), alloc_group)
			| xmalloc(&((elm)->data.str), (byte + 1), alloc_group))
			return (MEMORY_ERROR);
		(elm)->data.len = byte;
		byte = 0;
		while (*str && *str != sep)
			(elm)->data.str[byte++] = *(str)++;
		if (*head)
			(*head)->prev = elm;
		(elm)->next = *head;
		*head = (elm);
	}
	return (NO_ERROR);
}
