/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:37:59 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/20 14:16:44 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stdio.h>

void	close_fds(int fds)
{
	int	i;

	i = 0;
	while (fds > 0)
	{
		if (fds & 1)
		{
			close(i);
		}
		fds = fds >> 1;
		i++;
	}
}

void	close_all(int i)
{
	while (!close(i))
		i++;
}
