/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:27:01 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 16:23:26 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_exit(t_ctx *ctx, t_token *args)
{
	long	exit_status;

	(void)ctx;
	printf("exit\n");
	if (!args || !args->value.str)
		exit_status = ctx->old_status;
	else if (secure_atoi(args->value.str, &exit_status))
	{
		print_err(EXIT_ERROR, args->value.str);
		exit_status = 2;
	}
	else if (args && args->next)
	{
		print_custom_err("minishell: exit: too many arguments\n");
		return (1);
	}
	xfree_all();
	close_all();
	exit(exit_status % 256);
	return (NO_ERROR);
}
