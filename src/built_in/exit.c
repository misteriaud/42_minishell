/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:27:01 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 14:19:58 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_exit(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	(void)args;
	printf("exit\n");
	return (NO_ERROR);
}
