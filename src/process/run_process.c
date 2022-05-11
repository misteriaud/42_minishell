/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/11 11:31:13 by mriaud           ###   ########.fr       */
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

static inline t_err	run_cmd(t_ctx *ctx, t_token *token, int *dfd)
{
	char	**argv;
	t_func	*built_func;
	t_err	err;
	int		status;

	err = NO_ERROR;
	built_func = search_built_in(ctx, token->value.str);
	if (!err && !built_func)
		err = print_err(get_exec_path(ctx, &token->value), token->value.str);
	if (!err && token->in)
		redirect_in(token->in, &err, dfd);
	if (!err && token->redir)
		redirect_out(token->redir, &err, dfd);
	if (!err && !built_func)
		err = get_exec_arg(&argv, token);
	if (!err)
		err = package_env(ctx);
	if (!err && built_func)
		err = built_func(ctx, token->arg);
	else if (!err)
		execve(token->value.str, argv, ctx->exec_env);
	while (wait(&status) > 0)
		;
	return (err);
}

t_err	execute(t_ctx *ctx, t_token *token, int *dfd)
{
	int			pid;
	t_err		err;

	err = split_process(&pid, token);
	if (!pid)
	{
		err = run_cmd(ctx, token, dfd);
		close(dfd[0]);
		close(dfd[1]);
		close(0);
		close(1);
		close(2);
		xfree_all();
		exit(err);
	}
	if (pid && token->out)
		return (execute(ctx, token->out, dfd));
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
		exit_status = execute(ctx, curr, default_inout);
	else
		exit_status = run_cmd(ctx, curr, default_inout);
	dup2(default_inout[0], 0);
	dup2(default_inout[1], 1);
	close(default_inout[0]);
	close(default_inout[1]);
	if (get_status())
		return (get_status());
	return (exit_status);
}
