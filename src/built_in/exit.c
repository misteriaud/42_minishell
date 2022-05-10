/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:27:01 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 12:24:30 by mriaud           ###   ########.fr       */
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
		print_err(EXIT_ERROR, args->value.str);
		exit_status = 2;
	}
	xfree_all();
	close(0);
	close(1);
	close(2);
	exit(exit_status % 256);
	return (NO_ERROR);
}
