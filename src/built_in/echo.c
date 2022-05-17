/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/05/17 16:33:48 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_echo(t_ctx *ctx, t_token *args)
{
	int		state;

	(void)ctx;
	state = 1;
	if (args && args->value.str[0] == '-'
		&& args->value.str[1] == 'n')
	{
		state = 0;
		args = args->next;
	}
	while (args)
	{
		if (writer(1, args->value.str, args->value.len))
			return (1);
		args = args->next;
		if (args)
			if (writer(STDOUT_FILENO, " ", 1))
				return (1);
	}
	if (state)
		if (writer(STDOUT_FILENO, "\n", 1))
			return (1);
	return (NO_ERROR);
}
