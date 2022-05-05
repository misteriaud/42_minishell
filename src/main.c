/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/05 10:29:08 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <prompt.h>

static void	signal_handler(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

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
	// char *prompt;
	signal(SIGUSR1, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_handler);
		// get_prompt(&ctx, &prompt);
		// cmd = readline(prompt);
		cmd = readline("minishell > ");
		signal(SIGINT, SIG_IGN);
		if (!cmd)
			cmd_exit(NULL, NULL);
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
