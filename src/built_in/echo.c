/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/05/02 16:33:44 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_echo(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	int state;

	state = 1;
	if (args && args->value.str[0] == '-'
		&& args->value.str[1] == 'n')
	{
		state = 0;
		args = args->next;
	}
	while (args)
	{
		write(1, args->value.str, args->value.len);
		args = args->next;
		if (args)
			write(STDOUT_FILENO, " ", 1);
	}
	if (state)
		write(STDOUT_FILENO, "\n", 1);
	return (NO_ERROR);
}
