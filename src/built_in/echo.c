/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 12:23:36 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_echo(t_ctx *ctx, t_token *args)
{
	(void)ctx;

	while (args)
	{
		write(1, args->value.str, args->value.len);
		args = args->next;
	}
	//printf("echo\n");
	return (NO_ERROR);
}
