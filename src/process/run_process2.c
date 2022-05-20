/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:35:38 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/20 14:37:28 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

t_err	reinit_fds(int *default_inout, t_err exit_status)
{
	dup2(default_inout[0], 0);
	dup2(default_inout[1], 1);
	close(default_inout[0]);
	close(default_inout[1]);
	if (get_status())
		return (get_status());
	return (exit_status);
}
