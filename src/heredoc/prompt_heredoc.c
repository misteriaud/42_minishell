/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:29:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/20 14:17:24 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
		write(2, "\n", 1);
	close_all(0);
	xfree_all();
	exit(CTRL_C_ERROR);
}

static inline void	write_doc(t_ctx *ctx, char *eof)
{
	t_str	line;

	signal(SIGINT, signal_handler);
	signal(SIGUSR1, signal_handler);
	while (1)
	{
		if (readline_to_mem(&line))
		{
			close_all(0);
			xfree_all();
			exit (MEMORY_ERROR);
		}
		if (!line.str || !compare(line.str, eof) || (!eof && !line.len)
			|| drop_variables(ctx, &line))
		{
			if (!line.str)
				print_custom_err("here-doc recieve EOF\n");
			break ;
		}
		write(3, line.str, line.len);
		write(3, "\n", 1);
	}
	close_all(0);
	xfree_all();
	exit(NO_ERROR);
}

static inline t_err	recieve_doc(int *pfd, t_token *token)
{
	char	c;
	int		status;
	int		fd;
	char	*path;

	close(pfd[1]);
	if (get_tmp_path(&fd, &path))
		return (MEMORY_ERROR);
	while (read(pfd[0], &c, 1) == 1)
	{
		if (write(fd, &c, 1) == -1)
		{
			kill(0, SIGUSR1);
			return (MEMORY_ERROR);
		}
	}
	close(pfd[0]);
	close(fd);
	token->value.str = path;
	token->value.len = get_len(path);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (NO_ERROR);
}

static inline t_err	get_doc(t_ctx *ctx, t_token *token)
{
	int		pid;
	int		pfd[2];
	t_err	err;

	err = NO_ERROR;
	if (pipe(pfd) == -1)
		return (PIPE_ERROR);
	pid = fork();
	if (pid < 0)
		err = FORK_ERROR;
	if (!err && pid)
		err = recieve_doc(pfd, token);
	else if (!err && !pid)
	{
		close(pfd[0]);
		dup2(pfd[1], 3);
		close(pfd[1]);
		write_doc(ctx, token->value.str);
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
				err = get_doc(ctx, curr_in);
			curr_in = curr_in->next;
		}
		curr = curr->out;
	}
	return (err);
}
