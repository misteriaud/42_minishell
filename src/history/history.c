/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:53:26 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 21:17:57 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define HISTORY_FILE_NAME	".minishell_history"

int	init_history(t_ctx *ctx)
{
	char	*file;
	char	*home;
	t_str	history_path;

	get_env(ctx, "HOME", &home);
	merge(&history_path, home, "/.minishell_history");
	ctx->fd_history = open(history_path.str, O_RDWR | O_CREAT, 0666);
	if (ctx->fd_history < 0)
		return (OPEN_ERROR);
	get_file(ctx->fd_history, &file);
	split_lst_inverted(&(ctx->history), file, '\n', HISTORY_ALLOC);
	return (NO_ERROR);
}

int	add_history(t_ctx *ctx, const t_str cmd)
{
	t_lst	*new;

	write(ctx->fd_history, "\n", 1);
	write(ctx->fd_history, cmd.str, cmd.len);

	if (xmalloc(&new, sizeof(t_lst), HISTORY_ALLOC))
		return (MEMORY_ERROR);
	new->data = cmd;
	if (ctx->history)
		ctx->history->prev = new;
	new->next = ctx->history;
	ctx->history = new;
	return (NO_ERROR);
}
