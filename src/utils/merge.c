/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:41:30 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 20:52:07 by artblin          ###   ########.fr       */
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

t_err	merge(t_str *dest, char *str1, const char *str2)
{
	int		byte;
	int		x;

	x = 0;
	if (!str1 | !str2)
		return (NULL_PTR_ERROR);
	byte = len(str1) + len(str2);
	if (!byte)
		return (NO_BYTE_ERROR);
	if (xmalloc(&(dest->str), byte + 1, TMP_ALLOC))
		return (MEMORY_ERROR);
	while (*str1)
		dest->str[x++] = *(str1)++;
	while (*str2)
		dest->str[x++] = *(str2)++;
	return (NO_ERROR);
}
