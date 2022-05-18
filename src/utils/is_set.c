/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:22:54 by artblin           #+#    #+#             */
/*   Updated: 2022/05/17 15:18:35 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_set(const char c, const char *set)
{
	if (set)
	{
		while (*set)
		{
			if (c == *set)
				return (TRUE);
			set++;
		}
	}
	return (FALSE);
}

t_bool	is_containing_set(const char *str, const char *set)
{
	if (str && set)
	{
		while (*str)
		{
			if (is_set(*str, set))
				return (TRUE);
			str++;
		}
	}
	return (FALSE);
}

t_bool	is_only_set(const char *str, const char *set)
{
	if (str && set)
	{
		while (*str)
		{
			if (!is_set(*str, set))
				return (FALSE);
			str++;
		}
		return (TRUE);
	}
	return (FALSE);
}
