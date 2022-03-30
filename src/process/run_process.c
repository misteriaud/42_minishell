/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/30 12:40:55 by mriaud           ###   ########.fr       */
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

t_err	execute(t_ctx *ctx, t_token *token, t_err *err)
{
	pid_t	pid;
	int		pfd[2];
	char	**argv;
	t_func	*built_func;

	built_func = search_built_in(ctx, token->value.str);
	if (!built_func && get_exec_path(ctx, &token->value))
		return (BIN_UNKNOWN);
	if (token->out)
	{
		if (token->out && pipe(pfd) == -1)
			return (PIPE_ERROR);
		pid = fork();
		if (pid < 0)
			return (FORK_ERROR);
		if (pid == 0)
		{
			close(pfd[1]); /* close write side */
			dup2(pfd[0], 0); // connect read side with stdin
			close(pfd[0]); // close read side
			return (execute(ctx, token->out, err));
		}
		else
		{
			close(pfd[0]);
			dup2(pfd[1], 1); /* connect the write side with stdout */
			close(pfd[1]); /* close the write side */
		}
	}
	if (!built_func && get_exec_arg(&argv, token))
		return (MEMORY_ERROR);
	if (built_func)
		return (built_func(ctx, token->arg));
	execve(token->value.str, argv, NULL);
	return (NO_ERROR);
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
