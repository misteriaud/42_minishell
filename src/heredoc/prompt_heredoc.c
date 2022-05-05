/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:29:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/05 14:25:26 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
		write(2, "\n", 1);
	xfree_all();
	exit(CTRL_C_ERROR);
}

static inline void	write_doc(char *eof)
{
	t_str	line;

	line.str = NULL;
	line.len = 0;
	signal(SIGINT, signal_handler);
	signal(SIGUSR1, signal_handler);
	while (1)
	{
		line.str = readline("> ");
		line.len = get_len(line.str);
		if (!line.str || !compare(line.str, eof))
		{
			if (line.str)
				free(line.str);
			else
				print_custom_err("here-doc recieve EOF\n");
			break ;
		}
		write(3, line.str, line.len);
		write(3, "\n", 1);
		free(line.str);
	}
	close(3);
	exit(0);
}

static inline t_err	recieve_doc(t_ctx *ctx, int *pfd, t_str *dest)
{
	char	c;
	int		status;

	close(pfd[1]);
	while (read(pfd[0], &c, 1) == 1)
	{
		if (xrealloc(&(dest->str), ++dest->len + 1, PARS_ALLOC))
		{
			kill(0, SIGUSR1);
			return (MEMORY_ERROR);
		}
		dest->str[dest->len - 1] = c;
	}
	if (dest->str && drop_variables(ctx, dest))
		return (MEMORY_ERROR);
	close(pfd[0]);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (NO_ERROR);
}

static inline t_err	get_doc(t_ctx *ctx, t_str *dest)
{
	int		pid;
	int		pfd[2];
	t_err	err;
	char	*eof;

	eof = dest->str;
	dest->len = 0;
	dest->str = NULL;
	err = NO_ERROR;
	if (pipe(pfd) == -1)
		return (PIPE_ERROR);
	pid = fork();
	if (pid < 0)
		err = FORK_ERROR;
	if (!err && pid)
		err = recieve_doc(ctx, pfd, dest);
	else if (!err && !pid)
	{
		close(pfd[0]);
		dup2(pfd[1], 3);
		close(pfd[1]);
		write_doc(eof);
	}
	return (err);
}

t_err	prompt_heredoc(t_ctx *ctx)
{
	t_token	*curr;
	t_token	*curr_in;
	t_err	err;

	err = NO_ERROR;
	curr = ctx->parse_tree;
	while (!err && curr)
	{
		curr_in = curr->in;
		while (!err && curr_in)
		{
			if (curr_in->type == HEREDOC)
				err = get_doc(ctx, &curr_in->value);
			curr_in = curr_in->next;
		}
		curr = curr->out;
	}
	return (err);
}
