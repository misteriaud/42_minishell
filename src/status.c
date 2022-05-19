/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:07:03 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/19 15:01:44 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <status.h>

unsigned int	g_status;

unsigned int	get_status(void)
{
	return (g_status);
}

void	set_status(const unsigned int state)
{
	g_status = state;
}
