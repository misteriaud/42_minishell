/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:07:16 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/03 09:21:36 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

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
		{
			perror(path->value.str);
			return (REDIRECT_ERROR);
		}
		path = path->next;
	}
	return (NO_ERROR);
}

static inline void	stream_to_file(int *pfd, const int fd)
{
	char	c;

	close(pfd[1]);
	while (read(pfd[0], &c, 1) == 1)
		if (write(fd, &c, 1) == -1)
		{
			close(pfd[0]);
			perror("minishell : write error ");
			exit(WRITE_ERROR);
		}
	close(pfd[0]);
	close(fd);
	exit(NO_ERROR);
}

t_err	redirect_out(t_token *path, t_err *err)
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
		stream_to_file(pfd, fd);
	if (!*err)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
	}
	return (*err);
}
