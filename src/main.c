/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:54 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 16:54:53 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	t_ctx	ctx;
	init_term(&ctx);
	init_env(&ctx, env);
	init_history(&ctx);
	refresh_paths(&ctx);

	// t_str	prog = {"wc", 2};
	// get_exec_path(&ctx, &prog);
	// printf("prog -> %s\n", prog.str);
	//execve(prog.str, av, env);

	/*
	t_str str;

	str.str = "tutur utilise $SHELL!";
	printf("%s\n", str.str);
	replace_var(&ctx, &str);
	printf("%s\n", str.str);
	printf("%d\n", str.len);
	*/

	xfree_all();
	return (0);
}
