/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:27:49 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 12:28:00 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static inline void	assign_functions(t_ctx *ctx)
{
	ctx->built[CMD_CD].func = &cmd_cd;
	ctx->built[CMD_PWD].func = &cmd_pwd;
	ctx->built[CMD_ENV].func = &cmd_env;
	ctx->built[CMD_EXIT].func = &cmd_exit;
	ctx->built[CMD_ECHO].func = &cmd_echo;
	ctx->built[CMD_UNSET].func = &cmd_unset;
	ctx->built[CMD_EXPORT].func = &cmd_export;
}

t_err	init_built_in(t_ctx *ctx)
{
	int			x;
	int			len;
	char const	tmp[7][16] = {
		"cd", "pwd", "env", "exit", "echo", "unset", "export" };

	x = 0;
	while (x < BUILT_IN_NBR)
	{
		len = get_len(tmp[x]);
		if (new_str(&(ctx->built[x].cmd), len, BUILT_ALLOC))
			return (MEMORY_ERROR);
		str_fill(&(ctx->built[x].cmd), tmp[x]);
		x++;
	}
	assign_functions(ctx);
	return (NO_ERROR);
}
