/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:07:03 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/09 17:49:03 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <status.h>

static	unsigned int	*status(void)
{
	static unsigned int	state = 0;

	return (&state);
}

unsigned int	get_status(void)
{
	return (*status());
}

void	set_status(const unsigned int state)
{
	*(status()) = state;
}
