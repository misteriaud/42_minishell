/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:54 by mriaud            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/29 15:49:19 by mriaud           ###   ########.fr       */
=======
/*   Updated: 2022/03/29 16:54:53 by artblin          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;

	t_ctx	ctx;
	init_term(&ctx);
	init_env(&ctx, env);
	init_history(&ctx);
	refresh_paths(&ctx);

	if(parse(&ctx.parse_tree, av[1]))
		return (0);
	// t_str	prog = {"nvim", 4};
	// get_exec_path(&ctx, &prog);
	// printf("prog -> %s\n", prog.str);

	xfree_all();
	return (0);
}
