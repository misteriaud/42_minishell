/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:53:26 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 18:38:45 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define NO_ERROR			0
#define OPEN_ERROR			122
#define HISTORY_GROUP		130
#define MEMORY_ERROR		287
#define HISTORY_FILE_NAME	".minishell_history"


int	init_history(t_ctx *ctx)
{
	ctx->fd_history = open(".minishell_history",
			O_RDWR | O_CREAT, 0666);
	if (ctx->fd_history < 0)
		return (OPEN_ERROR);

	return (NO_ERROR);
}

int	history_parsing()
{
	return (0);
}

int	add_to_history(t_ctx *ctx, t_str cmd)
{
	t_lst	*new;

	write(ctx->fd_history, cmd.str, cmd.len);
	write(ctx->fd_history, "\n", 1);

	if (xmalloc(&new, sizeof(t_lst), HISTORY_ALLOC))
		return (MEMORY_ERROR);
	new->data = cmd;
	new->next = ctx->history;
	ctx->history = new;
	return (NO_ERROR);
}
