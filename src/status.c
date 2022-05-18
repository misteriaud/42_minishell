/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:07:03 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/17 14:51:06 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <status.h>

unsigned int	g_status;

static	unsigned int	*status(void)
{
	return (&g_status);
}

unsigned int	get_status(void)
{
	return (*status());
}

void	set_status(const unsigned int state)
{
	*(status()) = state;
}
