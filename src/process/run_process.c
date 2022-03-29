/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 22:49:38 by mriaud           ###   ########.fr       */
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

// return stdin
t_err	execute_bin(t_ctx *ctx, t_token *token, t_err *err)
{
	pid_t	pid;
	int		pfd[2];
	char	**argv;


	if (get_exec_path(ctx, &token->value))
		return (BIN_UNKNOWN);
	if (get_exec_arg(&argv, token))
		return (MEMORY_ERROR);
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
			return (execute_bin(ctx, token->out, err));
		}
	}
	close(pfd[0]);
	dup2(pfd[1], 1); /* connect the write side with stdout */
	close(pfd[1]); /* close the write side */
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
	return (execute_bin(ctx, curr, &err));
}
