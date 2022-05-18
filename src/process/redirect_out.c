/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:07:16 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/18 17:26:55 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static inline t_err	open_file(int *fd, t_token *path)
{
	while (path)
	{
		if (*fd > 2)
			close(*fd);
		if (!path->value.str)
		{
			print_custom_err("minishell: ambiguous redirect\n");
			return (1);
		}
		*fd = open(path->value.str, O_RDWR | O_CREAT
				| O_TRUNC * (path->type == PATH)
				| O_APPEND * (path->type == APPEND_PATH),
				0664);
		if (*fd == -1)
			return (print_err(UNKNOWN_PATH_ERROR, path->value.str));
		path = path->next;
	}
	return (NO_ERROR);
}

t_err	redirect_out(t_token *path)
{
	int		fd;
	t_err	err;

	fd = 0;
	err = NO_ERROR;
	if (!err)
		err = open_file(&fd, path);
	if (!err && dup2(fd, 1) == -1)
		return (OPEN_ERROR);
	return (err);
}
