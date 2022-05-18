/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:53:54 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/17 16:51:32 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stdio.h>

t_err	writer(int fd, char *str, unsigned int size)
{
	if (!str)
		return (NO_ERROR);
	if (write(fd, str, size) == -1)
	{
		perror("minishell: write error: ");
		return (WRITE_ERROR);
	}
	return (NO_ERROR);
}
