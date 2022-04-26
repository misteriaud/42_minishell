/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:09:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/26 23:28:25 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <process.h>

static inline t_err	split_process(int *pid, t_token *token)
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

static inline void	run_cmd(t_err *err, t_ctx *ctx, t_token *token)
{
	char	**argv;
	t_func	*built_func;

	built_func = search_built_in(ctx, token->value.str);
	if (!*err && !built_func)
		*err = get_exec_path(ctx, &token->value);
	if (!*err && token->in)
		*err = redirect_in(token->in, err);
	if (!*err && token->redir)
		*err = redirect_out(token->redir, err);
	if (!*err && !built_func)
		*err = get_exec_arg(&argv, token);
	if (!*err)
		*err = package_env(ctx);
	if (!*err && built_func)
		built_func(ctx, token->arg);
	else if (!*err)
		execve(token->value.str, argv, ctx->exec_env);
	if (*err)
		write(2, "problemo :(\n", 12);
	exit(1);
}

t_err	execute(t_ctx *ctx, t_token *token)
{
	int		pid;
	int		wpid;
	int		status;
	t_err	err;

	err = split_process(&pid, token);
	if (!pid)
		run_cmd(&err, ctx, token);
	if (pid && token->out)
		return (execute(ctx, token->out));
	close(0);
	close(1);
	wpid = wait(&status);
	while (wpid > 0)
		wpid = wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (err);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	return ;
}

t_err	run_process(t_ctx *ctx)
{
	t_token	*curr;
	t_err	exit_status;
	int		default_inout[2];

	default_inout[0] = dup(0);
	default_inout[1] = dup(1);
	curr = ctx->parse_tree;
	if (!curr)
		return (PARSING_ERROR);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		return (SIGNAL_ERROR);
	exit_status = execute(ctx, curr);
	dup2(default_inout[0], 0);
	dup2(default_inout[1], 1);
	close(default_inout[0]);
	close(default_inout[1]);
	return (exit_status);
}
