/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:27:01 by artblin           #+#    #+#             */
/*   Updated: 2022/05/04 12:00:38 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_exit(t_ctx *ctx, t_token *args)
{
	int	exit_status;

	(void)ctx;
	printf("exit\n");
	if (!args || !args->value.str)
		exit_status = 0;
	else if (secure_atoi(args->value.str, &exit_status))
	{
		putstr_err("minishell: exit: ");
		putstr_err(args->value.str);
		putstr_err(": numeric argument required\n");
	}
	xfree_all();
	exit(exit_status % 256);
	return (NO_ERROR);
}
