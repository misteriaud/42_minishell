/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:07:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/17 15:42:42 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static inline t_err	get_fd(int *fd, t_token **in)
{
	while (*in)
	{
		if ((*in)->type == PATH)
		{
			if (*fd > 2)
				close(*fd);
			if (is_dir((*in)->value.str))
				return (print_err(DIR_ERROR, (*in)->value.str));
			*fd = open((*in)->value.str, O_RDONLY);
			if (*fd == -1)
				return (print_err(UNKNOWN_PATH_ERROR, (*in)->value.str));
		}
		if (!(*in)->next)
			break ;
		*in = (*in)->next;
	}
	return (NO_ERROR);
}

t_err	redirect_in(t_token *in)
{
	int		fd;
	t_err	err;

	fd = 0;
	err = NO_ERROR;
	if (!err)
		err = get_fd(&fd, &in);
	if (!err && dup2(fd, 0) == -1)
		return (OPEN_ERROR);
	return (err);
}
