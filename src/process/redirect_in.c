/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:07:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/05 14:16:46 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static inline t_err	get_fd(int *fd, t_token **in)
{
	struct stat stats;

	while (*in)
	{
		if ((*in)->type == PATH)
		{
			if (*fd > 2)
				close(*fd);
			if (!stat((*in)->value.str, &stats))
				return (print_err(UNKNOWN_PATH_ERROR, (*in)->value.str));
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

static inline void	stream_from_file(int *pfd, t_token *in, const int fd)
{
	char	c;

	close(pfd[0]);
	while (in->type == PATH && read(fd, &c, 1) == 1)
		write(pfd[1], &c, 1);
	if (in->type == HEREDOC)
		write(pfd[1], in->value.str, in->value.len);
	close(pfd[1]);
	close(fd);
	exit(NO_ERROR);
}

t_err	redirect_in(t_token *in, t_err *err)
{
	int		pfd[2];
	int		fd;
	int		pid;

	fd = 0;
	if (!*err)
		*err = get_fd(&fd, &in);
	if (!*err && pipe(pfd) == -1)
		*err = PIPE_ERROR;
	if (!*err)
		pid = fork();
	if (!*err && pid < 0)
		*err = FORK_ERROR;
	if (!*err && !pid)
		stream_from_file(pfd, in, fd);
	if (!*err)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
	}
	return (*err);
}
