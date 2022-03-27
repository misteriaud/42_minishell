/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:54 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/27 20:36:29 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_err	error;

	error = NO_ERROR;
	t_ctx	ctx;
	init_term(&ctx);
	ctx.history = NULL;
	while (error != READLINE_CTRL_D)
	{
		error = xreadline(&ctx, getcwd(NULL, 0));
		if (!error)
			printf("result: %s\n", ctx.curr_cmd.str);
	}
	xfree_all();
	return (0);
}
