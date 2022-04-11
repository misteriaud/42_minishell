/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/11 13:37:40 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>
#include <stdio.h>

static inline t_err	execute_next_token(t_ctx *ctx, t_token *next)
{
	int		pfd[2];
	int		pid;
	t_err	err;

	err = NO_ERROR;
	if (next && pipe(pfd) == -1)
		err = PIPE_ERROR;
	if (err)
		return (err);
	pid = fork();
	if (pid < 0)
		err = FORK_ERROR;
	if (!err && pid != 0)
	{
		close(pfd[1]); /* close write side */
		dup2(pfd[0], 0); // connect read side with stdin
		close(pfd[0]); // close read side
		execute(ctx, next);
	}
	if (!err)
	{
		close(pfd[0]);
		dup2(pfd[1], 1); /* connect the write side with stdout */
		close(pfd[1]); /* close the write side */
	}
	return (err);
}

static inline t_err	redirect_in(t_token *path, t_err *err)
{
	int		pfd[2];
	int		fd;
	int		pid;
	char	c;

	fd = 0;
	while (!*err && path)
	{
		close(fd);
		fd = open(path->value.str, O_RDONLY);
		if (fd == -1)
			return(REDIRECT_ERROR);
		path = path->next;
	}
	if (!*err && pipe(pfd) == -1)
		*err = PIPE_ERROR;
	if (!*err)
		pid = fork();
	if (!*err && pid < 0)
		*err = FORK_ERROR;
	if (!*err && pid == 0)
	{
		close(pfd[0]);
		while (read(fd, &c, 1))
			write(pfd[1], &c, 1);
		close(pfd[1]); // close write side
		close(fd);
		exit(NO_ERROR);
	}
	if (!*err)
	{
		close(pfd[1]); // close write side
		dup2(pfd[0], 0); /* connect the read side with stdin */
		close(pfd[0]); /* close the read side */
	}
	return (*err);
}

static inline t_err	redirect_out(t_token *path, t_err *err)
{
	int		pfd[2];
	int		fd;
	int		pid;
	char	c;

	fd = 0;
	while (!*err && path)
	{
		close(fd);
		fd = open(path->value.str, O_RDWR | O_CREAT
			| O_TRUNC * (path->type == PATH)
			| O_APPEND * (path->type == APPEND_PATH)
			, 0664);
		if (fd == -1)
			return(REDIRECT_ERROR);
		path = path->next;
	}
	if (!*err && pipe(pfd) == -1)
		*err = PIPE_ERROR;
	if (!*err)
		pid = fork();
	if (!*err && pid < 0)
		*err = FORK_ERROR;
	if (!*err && pid == 0)
	{
		close(pfd[1]); /* close write side */
		while(read(pfd[0], &c, 1))
			write(fd, &c, 1);
		close(pfd[0]); // close read side
		close(fd);
		exit(NO_ERROR);
	}
	if (!*err)
	{
		close(pfd[0]);
		dup2(pfd[1], 1); /* connect the write side with stdout */
		close(pfd[1]); /* close the write side */
	}
	return (*err);
}

void	execute(t_ctx *ctx, t_token *token)
{
	char	**argv;
	t_func	*built_func;
	int		pid;
	int		status;
	int		wpid;
	t_err	err;

	err = NO_ERROR;
	built_func = search_built_in(ctx, token->value.str);
	if (!err && !built_func)
		err = get_exec_path(ctx, &token->value);
	if (!err && token->redir)
		err = redirect_out(token->redir, &err);
	if (!err && token->in)
		err = redirect_in(token->in, &err);
	if (!token->redir && token->out)
		execute_next_token(ctx, token->out);
	if (!err && !built_func)
		err = get_exec_arg(&argv, token);
	if (!err)
		err = package_env(ctx);
	pid = fork();
	if (pid == 0 && !err && built_func)
		built_func(ctx, token->arg);
	else if (pid == 0 && !err)
		execve(token->value.str, argv, ctx->exec_env);
	while ((wpid = wait(&status)) > 0);
	if (pid && err)
		write(2, "error\n", 6);
	exit(err);
}

t_err	run_process(t_ctx *ctx)
{
	t_token *curr;
	int		pid, wpid;
	int		status;

	curr = ctx->parse_tree;
	if (!curr)
		return (PARSING_ERROR);
	pid = fork();
	if (pid == 0)
		execute(ctx, curr);
	while ((wpid = wait(&status)) > 0);
	return (NO_ERROR);
}
