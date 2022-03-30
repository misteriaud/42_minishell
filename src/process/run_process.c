/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/30 22:37:15 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>
#include <stdio.h>

static inline t_err	execute_next_token(t_ctx *ctx, t_token *next, int *pfd, t_err *err)
{
	int	pid;

	if (!*err && next && pipe(pfd) == -1)
		*err = PIPE_ERROR;
	if (!*err)
		pid = fork();
	if (!*err && pid < 0)
		*err = FORK_ERROR;
	if (!*err && pid == 0)
	{
		close(pfd[1]); /* close write side */
		dup2(pfd[0], 0); // connect read side with stdin
		close(pfd[0]); // close read side
		return (execute(ctx, next, err));
	}
	if (!*err)
	{
		close(pfd[0]);
		dup2(pfd[1], 1); /* connect the write side with stdout */
		close(pfd[1]); /* close the write side */
	}
	return (*err);
}

static inline t_err	redirect_out(t_token *path, int *pfd, t_err *err)
{
	int		fd;
	int		pid;
	char	c;

	fd = 0;
	while (!*err && path)
	{
		close(fd);
		fd = open(path->value.str, O_RDWR | O_CREAT | O_APPEND * (path->type == APPEND_PATH), 0664);
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
		// dup2(pfd[0], 0); // connect read side with stdin
		// close(pfd[0]); // close read side
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

t_err	execute(t_ctx *ctx, t_token *token, t_err *err)
{
	int		pfd[2];
	char	**argv;
	t_func	*built_func;

	built_func = search_built_in(ctx, token->value.str);
	if (!*err && !built_func)
		*err = get_exec_path(ctx, &token->value);
	if (!*err && token->redir)
		*err = redirect_out(token->redir, pfd, err);
	else if (!*err && token->out)
		*err = execute_next_token(ctx, token->out, pfd, err);
	if (!*err && !built_func)
		*err = get_exec_arg(&argv, token);
	if (!*err)
		*err = package_env(ctx);
	if (!*err && built_func)
		built_func(ctx, token->arg);
	else if (!*err)
		execve(token->value.str, argv, ctx->exec_env);
	return (*err);
}

t_err	run_process(t_ctx *ctx)
{
	t_token *curr;
	t_err	err;

	err = NO_ERROR;
	curr = ctx->parse_tree;
	if (!curr)
		return (PARSING_ERROR);
	return (execute(ctx, curr, &err));
}
