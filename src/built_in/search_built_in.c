/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 01:12:33 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 16:38:13 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_func	*search_built_in(t_ctx *ctx, const char *exec)
{
	int		x;

	x = 0;
	while (x < BUILT_IN_NBR)
	{
		if (!compare(exec, ctx->built[x].cmd.str))
			return ((ctx->built[x].func));
		x++;
	}
	return (NULL);
}
