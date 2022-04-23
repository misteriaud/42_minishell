/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/23 20:02:00 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>
#include <stdio.h>
#include <unistd.h>

static inline t_err split_process(int *pid, t_token *token)
{
	int		pfd[2];
	t_err	err;

	err = NO_ERROR;
	if (token->out && !token->redir && pipe(pfd) == -1)
		err = PIPE_ERROR;
	if (err)
		return (err);
	*pid = fork();
	if (*pid < 0)
		err = FORK_ERROR;
	if (!err && token->out && !token->redir && *pid)
	{
		close(pfd[1]); /* close write side */
		dup2(pfd[0], 0); // connect read side with stdin
		close(pfd[0]); // close read side
	}
	else if (!err && token->out && !token->redir && !*pid)
	{
		close(pfd[0]);
		dup2(pfd[1], 1); /* connect the write side with stdout */
		close(pfd[1]); /* close the write side */
	}
	return (err);
}

static inline t_err	redirect_in(t_token *in, t_err *err)
{
	int		pfd[2];
	int		fd;
	int		pid;
	char	c;

	fd = 0;
	while (!*err && in)
	{
		if (in->type == PATH)
		{
			close(fd);
			fd = open(in->value.str, O_RDONLY);
			if (fd == -1)
				return(REDIRECT_ERROR);
		}
		if (!in->next)
			break;
		in = in->next;
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
		while (in->type == PATH && read(fd, &c, 1) == 1)
			write(pfd[1], &c, 1);
		if (in->type == HEREDOC)
			write(pfd[1], in->value.str, in->value.len);
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
		if (fd)
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
		while (read(pfd[0], &c, 1) == 1)
			if (write(fd, &c, 1) == -1)
				write(2, "write error\n", 12);
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

t_err	execute(t_ctx *ctx, t_token *token)
{
	char	**argv;
	t_func	*built_func;
	int		pid;
	int		status, wpid;
	t_err	err;

	err = split_process(&pid, token);
	if (!pid)
	{
		built_func = search_built_in(ctx, token->value.str);
		if (!err && !built_func)
			err = get_exec_path(ctx, &token->value);
		if (!err && token->in)
			err = redirect_in(token->in, &err);
		if (!err && token->redir)
			err = redirect_out(token->redir, &err);
		if (!err && !built_func)
			err = get_exec_arg(&argv, token);
		if (!err)
			err = package_env(ctx);
		if (!err && built_func)
			built_func(ctx, token->arg);
		else if (!err)
			execve(token->value.str, argv, ctx->exec_env);
		if (err)
			write(2, "problemo :(\n", 12);
		exit(1);
	}
	if (pid && token->out)
		return (execute(ctx, token->out));
	waitpid(0, &status, 0);
	close(0);
	close(1);
	while ((wpid = wait(&status)) > 0);
	return(err);
}

t_err	run_process(t_ctx *ctx)
{
	t_token *curr;
	t_err	err;
	int		default_inout[2];
	default_inout[0] = dup(0);
	default_inout[1] = dup(1);

	curr = ctx->parse_tree;
	if (!curr)
		return (PARSING_ERROR);
	err = execute(ctx, curr);
	dup2(default_inout[0], 0);
	dup2(default_inout[1], 1);
	close(default_inout[0]);
	close(default_inout[1]);
	return (err);
}
