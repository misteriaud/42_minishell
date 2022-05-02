/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/02 16:12:37 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <prompt.h>


int	main(int ac, char **av, char **env)
{
	t_ctx	ctx;
	t_err	err;
	char	*cmd;

	(void)av;

	if (ac != 1)
		return (1);
	err = NO_ERROR;
	//init_term(&ctx);
	init_env(&ctx, env);
	// init_history(&ctx);
	init_built_in(&ctx);

	//char *prompt;

	while (1)
	{
		//get_prompt(&ctx, &prompt);
		//cmd = readline(prompt);
		cmd = readline("minishell > ");
		if (!cmd)
			return (0);
		refresh_paths(&ctx);
		err = parse(&ctx, cmd);
		if (!err)
			err = prompt_heredoc(&ctx);
		if (!err)
			err = run_process(&ctx);
		if (err)
			printf("err : %d\n", err);
		free(cmd);

	}
	xfree_all();
	return (0);
}
