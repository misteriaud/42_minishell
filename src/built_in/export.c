/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:50 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 14:20:28 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_export(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	(void)args;
	printf("export\n");
	return (NO_ERROR);
}
