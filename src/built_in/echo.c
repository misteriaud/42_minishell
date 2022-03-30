/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 15:30:24 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_echo(t_ctx *ctx, t_token *args)
{
	(void)ctx;

	while (args)
	{
		write(1, args->value.str, args->value.len);
		args = args->next;
	}
	//printf("echo\n");
	exit(NO_ERROR);
}
