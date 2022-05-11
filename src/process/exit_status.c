/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:06:49 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/11 09:16:45 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

t_err	get_exit_status(void)
{
	int			wpid;
	int			status;
	int			highest_pid;
	int			highest_status;
	t_err		err;

	wpid = 0;
	status = 0;
	err = NO_ERROR;
	wpid = wait(&status);
	highest_pid = wpid;
	highest_status = status;
	while (wpid > -1)
	{
		if (wpid > highest_pid)
			highest_status = status;
		wpid = wait(&status);
	}
	if (wpid && WIFEXITED(highest_status))
		err = WEXITSTATUS(highest_status);
	return (err);
}
