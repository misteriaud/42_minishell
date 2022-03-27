/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:43:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 17:17:19 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	token_count(const char *str, int *nbr_token, const char sep)
{
	*nbr_token = 0;
	if (!str)
		return (NULL_PTR_ERROR);
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str && *str != sep)
			(*nbr_token)++;
		while (*str && *str != sep)
			str++;
	}
	if (!(*nbr_token))
		return (NO_TOKEN_ERROR);
	return (NO_ERROR);
}

t_err	byte_count(const char *str, int *nbr_byte, const char sep)
{
	*nbr_byte = 0;

	while (*str && *str != sep)
	{
		(*nbr_byte)++;
		str++;
	}
	if (!(*nbr_byte))
		return (NO_BYTE_ERROR);
	return (NO_ERROR);
}

t_err	fill_double_array(char **tab, const char *str, const char sep, const int alloc_group)
{
	int		byte;
	int		w;
	int		b;

	w = 0;
	while (*str)
	{
		while (*str == sep)
			str++;
		if (byte_count(str, &byte, sep))
			break ;
		if (xmalloc(&tab[w], byte + 1, alloc_group))
			return (MEMORY_ERROR);
		b = -1;
		tab[w][byte] = '\0';
		while (++b < byte)
			tab[w][b] = *(str)++;
		w++;
	}
	return (NO_ERROR);
}

t_err	split_arr(char ***array, const char *str, const char sep, const int alloc_group)
{
	char	**tab;
	int		word;
	int		err;

	if (!str)
		return (NULL_PTR_ERROR);
	err = token_count(str, &word, sep);
	if (err)
		return (err);
	if (xmalloc(&tab, (word + 1) * sizeof(char *), alloc_group))
		return (MEMORY_ERROR);
	tab[word] = NULL;
	if (fill_double_array(tab, str, sep, alloc_group))
		return (MEMORY_ERROR);
	*array = tab;
	return (NO_ERROR);
}

t_err	split_lst(t_lst **head, const char *str,  const char sep, const int alloc_group)
{
	t_lst	**elm;
	int		byte;

	head = NULL;
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
		(*elm)->data.str[byte] = '\0';
		(*elm)->data.len = byte;
		byte = 0;
		while (*str && *str != sep)
			(*elm)->data.str[byte++] = *(str)++;
		elm = &((*elm)->next);
	}
	return (NO_ERROR);
}
