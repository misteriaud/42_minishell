/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/04/27 17:08:24 by artblin          ###   ########.fr       */
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
		if (args)
			write(1, " ", 1);
		else
			write(1, "\n", 1);
	}
	return (NO_ERROR);
	//exit(NO_ERROR);
}
