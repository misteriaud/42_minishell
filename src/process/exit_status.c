/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:06:49 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/09 12:26:18 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static t_err	wait_for_process(t_wstatus **wstatus)
{
	int				i;

	i = 0;
	if (xrealloc(wstatus, sizeof(**wstatus) * ++i, EXEC_ALLOC))
		return (MEMORY_ERROR);
	(*wstatus)[i - 1].pid = wait(&(*wstatus)[i - 1].status);
	while ((*wstatus)[i - 1].pid > 0)
	{
		if (xrealloc(wstatus, sizeof(**wstatus) * ++i, EXEC_ALLOC))
			return (MEMORY_ERROR);
		(*wstatus)[i - 1].pid = wait(&(*wstatus)[i - 1].status);
	}
	return (NO_ERROR);
}

t_err	get_exit_status(void)
{
	t_wstatus	*wstatus;
	int			i;
	int			highest;
	t_err		err;

	i = 0;
	wstatus = NULL;
	err = NO_ERROR;
	if (wait_for_process(&wstatus))
		return (MEMORY_ERROR);
	highest = 0;
	while (wstatus && wstatus[++i].pid != -1)
	{
		if (wstatus[i].pid > wstatus[highest].pid)
			highest = i;
	}
	if (WIFEXITED(wstatus[highest].status))
		err = WEXITSTATUS(wstatus[highest].status);
	return (err);
}
