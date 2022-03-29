/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 22:03:59 by mriaud           ###   ########.fr       */
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
	t_token *curr_arg;
	// t_token *curr_in;
	int		pfd[2];
	char	c;

	curr_arg = token->arg;
	if (token->type == CMD)
	{
		if (get_exec_path(ctx, &token->value))
			return (BIN_UNKNOWN);
		printf("\n-> %s \n", token->value.str);
		if (token->out && pipe(pfd) == -1)
		{
			printf("pipe failed\n");
			return 1;
		}
		while (token->fd[0] && read(token->fd[0], &c, 1) != 1)
			write(1, &c, 1);
	}
	// if (token->type == PATH)
	// 	printf("\n-> save to %s", token->value.str);
	while (curr_arg)
	{
		printf("%s ", curr_arg->value.str);
		fflush(stdout);
		curr_arg = curr_arg->next;
	}
	if (token->out)
	{
		pid = fork();
		if (pid < 0)
			*err = FORK_ERROR;
		if (pid == 0)
		{
			token->fd[0] = pfd[0];
			close(pfd[1]); /* close write side */
			return (execute_bin(ctx, token->out, err));
		}
		else
		{
			close(pfd[0]);
			write(pfd[1], "hello", 5);
			close(pfd[1]);
			printf("\nparent process : ");

		}
	}
	return (0);
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
