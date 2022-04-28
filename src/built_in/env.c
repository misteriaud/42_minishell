/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:25 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 10:08:39 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_env(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	(void)args;
	printf("env\n");
	return (NO_ERROR);
}
