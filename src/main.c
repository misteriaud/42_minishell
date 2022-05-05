/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/05 14:15:33 by mriaud           ###   ########.fr       */
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

static inline void free_cmd(char *cmd)
{
	free(cmd);
	xfree_group(PARS_ALLOC);
	xfree_group(EXEC_ALLOC);
	xfree_group(TMP_ALLOC);
}

int	main(int ac, char **av, char **env)
{
	t_ctx	ctx;
	char	*cmd;

	(void)av;

	if (ac != 1)
		return (1);
	init_env(&ctx, env);
	init_built_in(&ctx);
	ctx.status = NO_ERROR;
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
		ctx.status = parse(&ctx, cmd);
		if (!ctx.status)
			ctx.status = prompt_heredoc(&ctx);
		if (!ctx.status)
			ctx.status = run_process(&ctx);
		print_err(ctx.status, NULL);
		free_cmd(cmd);
	}
	xfree_all();
	return (0);
}
