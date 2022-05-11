/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:08:32 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 18:08:57 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	compare(const char *what, const char *with)
{
	if (!what | !with)
		return (NULL_PTR_ERROR);
	while (*what && *with && *what == *with)
	{
		what++;
		with++;
	}
	if (*what != *with)
		return (NOT_EQUAL_ERROR);
	return (NO_ERROR);
}
