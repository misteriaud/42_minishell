/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/30 13:42:01 by artblin          ###   ########.fr       */
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
	init_built_in(&ctx);

	t_func	*f;

	f = search_built_in(&ctx, "export");
	if (f)
		f(&ctx, NULL);

	//print_env(&ctx);
	package_env(&ctx);
	/*
	if(parse(&ctx, av[1]))
		return (0);
		*/

	xfree_all();
	return (0);
}

// test drop_variables
	/*t_str str;
	str.str = "tutur.utilise.$_!";
	printf("%s\n", str.str);
	drop_variables(&ctx, &str);
	printf("%s\n", str.str);
	printf("%d\n", str.len);*/
// test execve
	/*t_str	prog;
	if (ac > 1)
		prog.str = av[1];
	else
		prog.str = "";
	prog.len = get_len(prog.str);
	if (!get_exec_path(&ctx, &prog))
		execve(prog.str, av+1, env);
	else
		printf("bad exec!\n");*/
