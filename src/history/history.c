/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:53:26 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 22:35:30 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define HST_FILE_NAME	".minishell_history"
#define HST_FILE_LEN	18

int	init_history(t_ctx *ctx)
{
	t_str			home;
	const t_str		history_file = {HST_FILE_NAME, HST_FILE_LEN};
	t_str			history_path;
	char			*file;

	get_variable(ctx, "HOME", &home);
	if (new_str(&history_path, home.len + history_file.len, TMP_ALLOC))
		return (MEMORY_ERROR);
	merge(&history_path, &home, (t_str *)&history_file, '/');
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
