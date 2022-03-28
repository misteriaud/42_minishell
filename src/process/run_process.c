/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/28 18:23:35 by mriaud           ###   ########.fr       */
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
	t_token	*curr_out;

	curr_arg = token->arg;
	if (token->type == CMD)
	{
		if (get_exec_path(ctx, &token->value))
			return (BIN_UNKNOWN);
		printf("\n-> %s ", token->value.str);
	}
	if (token->type == PATH)
		printf("\n-> save to %s", token->value.str);
	fflush(stdout);
	while (curr_arg)
	{
		printf("%s ", curr_arg->value.str);
		fflush(stdout);
		curr_arg = curr_arg->next;
	}
	curr_out = token->out;
	while (curr_out)
	{
		if (curr_out->next)
			pid = fork();
		if (pid < 0)
			*err = FORK_ERROR;
		if (pid) //child
			return (execute_bin(ctx, curr_out, err));
		// printf("\nparent process : ");
		curr_out = curr_out->next;
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
