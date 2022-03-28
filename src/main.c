/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:54 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/28 18:26:22 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_ctx	ctx;
	t_err	err;

	if (ac != 2)
		return (1);
	err = NO_ERROR;
	init_term(&ctx);
	init_env(&ctx, env);
	init_history(&ctx);
	refresh_paths(&ctx);
	err = parse(&ctx.parse_tree, av[1]);
	if (!err)
		err = run_process(&ctx);
	xfree_all();
	printf("\n end of process(%x)\n", err);
	return (0);
}
