/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/30 12:44:27 by mriaud           ###   ########.fr       */
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
	err = parse(&ctx, av[1]);
	if (!err)
		err = run_process(&ctx);
	xfree_all();
	// printf("\n end of process(%x)\n", err);
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
