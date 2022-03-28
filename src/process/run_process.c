/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/28 14:21:29 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>
#include <stdio.h>

t_err	execute_builtin(t_token *token)
{
	(void)token;
	return (NO_ERROR);
}

t_err	execute_bin(t_token *token)
{
	t_token *curr_arg;

	if (!token)
	{
		printf("out\n");
		return (NO_ERROR);
	}
	curr_arg = token->arg;
	printf("%s with args [", token->value.str);
	while (curr_arg)
	{
		printf("%s (%d), ", curr_arg->value.str, curr_arg->type);
		curr_arg = curr_arg->next;
	}
	printf("] -> ");
	return (execute_bin(token->out));
}

t_err	run_process(t_ctx *ctx)
{
	t_token *curr;
	t_err	err;

	err = NO_ERROR;
	curr = ctx->parse_tree;
	if (!curr)
		return (err);
	err = execute_bin(curr);
	return (err);
}
