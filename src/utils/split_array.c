/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:13:11 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 22:17:36 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_err	fill_double_array(char **tab, const char *str, const char sep, const int alloc_group)
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
		b = 0;
		tab[w][byte] = '\0';
		while (b < byte)
			tab[w][b++] = *(str)++;
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
