/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 16:30:18 by mriaud           ###   ########.fr       */
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
		if (args)
			write(1, " ", 1);
		else
			write(1, "\n", 1);
	}
	exit(NO_ERROR);
}
