/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/20 15:19:26 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static inline t_err	split_process(int *pid, t_token *token)
{
	int		pfd[2];
	t_err	err;

	err = NO_ERROR;
	if (token->out && !token->redir && pipe(pfd) == -1)
		return (PIPE_ERROR);
	*pid = fork();
	if (*pid < 0)
		err = FORK_ERROR;
	if (!err && token->out && !token->redir && *pid)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
	}
	else if (!err && token->out && !token->redir && !*pid)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
	}
	return (err);
}

static inline t_err	run_cmd(t_ctx *ctx, t_token *token)
{
	char	**argv;
	t_func	*built_func;
	t_err	err;
	int		status;

	err = NO_ERROR;
	built_func = search_built_in(ctx, token->value.str);
	if (!err && !built_func && token->value.len > 0)
		err = print_err(get_exec_path(ctx, &token->value), token->value.str);
	if (!err && token->in)
		err = redirect_in(token->in);
	if (!err && token->redir)
		err = redirect_out(token->redir);
	if (!err && !built_func)
		err = get_exec_arg(&argv, token);
	if (!err)
		err = package_env(ctx);
	if (!err && built_func)
		err = built_func(ctx, token->arg);
	else if (!err && token->value.len > 0)
		execve(token->value.str, argv, ctx->exec_env);
	while (wait(&status) > 0)
		;
	return (err);
}

t_err	execute(t_ctx *ctx, t_token *token)
{
	int			pid;
	t_err		err;

	err = split_process(&pid, token);
	if (!pid)
	{
		err = run_cmd(ctx, token);
		close_all(0);
		xfree_all();
		exit(err);
	}
	if (pid && token->out)
		return (execute(ctx, token->out));
	close(0);
	close(1);
	if (!err)
		err = get_exit_status();
	return (err);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	set_status(CTRL_C_ERROR);
	write(2, "\n", 1);
}

t_err	run_process(t_ctx *ctx)
{
	t_token	*curr;
	t_err	exit_status;
	int		default_inout[2];
	t_func	*built_in;

	default_inout[0] = dup(0);
	default_inout[1] = dup(1);
	curr = ctx->parse_tree;
	if (!curr)
		return (PARSING_ERROR);
	built_in = search_built_in(ctx, curr->value.str);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		return (SIGNAL_ERROR);
	if (curr->out || !built_in)
		exit_status = execute(ctx, curr);
	else
	{
		exit_status = run_cmd(ctx, curr);
		close_all(5);
	}
	return (reinit_fds(default_inout, exit_status));
}
