/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:07:16 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/11 13:49:47 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static void	sigint_handler(int sig)
{
	(void)sig;
	close(0);
	close(1);
	close(2);
	xfree_all();
}

static inline t_err	open_file(int *fd, t_token *path)
{
	while (path)
	{
		if (*fd)
			close(*fd);
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

static inline void	stream_to_file(int *pfd, const int fd, int *dfd)
{
	char	c;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit(SIGNAL_ERROR);
	close(pfd[1]);
	while (read(pfd[0], &c, 1) == 1)
	{
		if (write(fd, &c, 1) == -1)
		{
			close(pfd[0]);
			print_err(UNKNOWN_PATH_ERROR, NULL);
			xfree_all();
			exit(UNKNOWN_PATH_ERROR);
		}
	}
	close(dfd[0]);
	close(dfd[1]);
	close(pfd[0]);
	close(fd);
	close(0);
	close(1);
	xfree_all();
	exit(NO_ERROR);
}

t_err	redirect_out(t_token *path, t_err *err, int *dfd)
{
	int		pfd[2];
	int		fd;
	int		pid;

	fd = 0;
	if (!*err)
		*err = open_file(&fd, path);
	if (!*err && pipe(pfd) == -1)
		*err = PIPE_ERROR;
	if (!*err)
		pid = fork();
	if (!*err && pid < 0)
		*err = FORK_ERROR;
	if (!*err && pid == 0)
		stream_to_file(pfd, fd, dfd);
	if (!*err)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		if (fd > 2)
			close(fd);
	}
	return (*err);
}
