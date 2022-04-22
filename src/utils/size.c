/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:09:41 by artblin           #+#    #+#             */
/*   Updated: 2022/04/21 19:21:01 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_len(const char *str)
{
	int		len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

t_err	byte_count(const char *str, int *nbr_byte, const char sep)
{
	*nbr_byte = 0;
	if (!str)
		return (NULL_PTR_ERROR);
	while (*str && *str != sep)
	{
		(*nbr_byte)++;
		str++;
	}
	if (!(*nbr_byte))
		return (NO_BYTE_ERROR);
	return (NO_ERROR);
}

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
