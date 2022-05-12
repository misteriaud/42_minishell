/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:28:36 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/12 09:33:41 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

t_bool	is_empty_str(char *str)
{
	if (!str)
		return (TRUE);
	if (!*str)
		return (TRUE);
	while (*str)
	{
		if (*str != ' ' || (*str > 8 && *str < 14))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
