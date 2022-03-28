/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:54 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/28 14:05:50 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_ctx	ctx;

	if (ac != 2)
		return (1);
	init_term(&ctx);
	init_env(&ctx, env);
	init_history(&ctx);
	if (parse(&ctx.parse_tree, av[1]))
		return (1);
	if (run_process(&ctx))
		return (1);
	xfree_all();
	return (0);
}
