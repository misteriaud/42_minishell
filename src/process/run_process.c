/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/30 15:15:28 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>
#include <stdio.h>

int	execute_builtin(t_token *token, t_err *err)
{
	(void)token;
	(void)err;
	return (NO_ERROR);
}

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

t_err	execute(t_ctx *ctx, t_token *token, t_err *err)
{
	int		pfd[2];
	char	**argv;
	t_func	*built_func;

	built_func = search_built_in(ctx, token->value.str);
	if (!*err && !built_func)
		*err = get_exec_path(ctx, &token->value);
	if (!*err && token->out)
		*err = execute_next_token(ctx, token->out, pfd, err);
	if (!*err && !built_func)
		*err = get_exec_arg(&argv, token);
	if (!*err && built_func)
		built_func(ctx, token->arg);
	else if (!*err)
		execve(token->value.str, argv, NULL);
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
