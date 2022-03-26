/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:53:26 by artblin           #+#    #+#             */
/*   Updated: 2022/03/26 21:17:33 by artblin          ###   ########.fr       */
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
			O_RDWR | O_CREAT | O_SYMLINK, 0666);
	if (ctx->fd_history < 0)
		return (OPEN_ERROR);


	t_hst	*new;
	char	*line;

	line = get_next_line(ctx->fd_history);
	while (line)
	{
		if (xmalloc(&new, sizeof(t_hst), HISTORY_GROUP))
			return (MEMORY_ERROR);
		new->cmd.str = line;
		new->next = ctx->history;
		ctx->history = new;
		line = get_next_line(ctx->fd_history);
	}



	// debug !!!
	t_hst *elm = ctx->history;
	printf("run hst_lst\n");
	while (elm)
	{
		printf("-> %s", elm->cmd.str);
		elm = elm->next;
	}
	printf("end run ///\n");
	return (NO_ERROR);
}

int	history_parsing()
{
	return (0);
}

int	add_to_history(t_ctx *ctx, t_str cmd)
{
	t_hst	*new;

	write(ctx->fd_history, cmd.str, cmd.len);
	write(ctx->fd_history, "\n", 1);

	if (xmalloc(&new, sizeof(t_hst), HISTORY_GROUP))
		return (MEMORY_ERROR);
	new->cmd = cmd;
	new->next = ctx->history;
	ctx->history = new;
	return (NO_ERROR);
}
