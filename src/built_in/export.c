/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:50 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 15:31:05 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_export(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	(void)args;
	printf("export\n");
	exit(NO_ERROR);
}
