/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/06 17:43:10 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <prompt.h>
#include <status.h>

#define RUNNING 1

static void	signal_handler(int signum)
{
	(void)signum;
	set_status(CTRL_C_ERROR);
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

void init_minishell(t_ctx *ctx, char **env)
{
	init_env(ctx, env);
	init_built_in(ctx);
	set_status(NO_ERROR);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_ctx	ctx;
	char	*cmd;
	char	*prompt;

	if (ac != 1)
		return (1);
	init_minishell(&ctx, env);
	while (RUNNING)
	{
		signal(SIGINT, signal_handler);
		get_prompt(&prompt);
		set_status(NO_ERROR);
		cmd = readline(prompt);
		xfree(prompt, PROMPT_ALLOC);
		signal(SIGINT, SIG_IGN);
		if (!cmd)
			cmd_exit(NULL, NULL);
		refresh_paths(&ctx);
		if (!get_status())
			set_status(parse(&ctx, cmd));
		if (get_status() == EMPTY_STR_ERROR)
		{
			set_status(0);
			free_cmd(cmd);
			continue;
		}
		if (!get_status())
			set_status(prompt_heredoc(&ctx));
		if (!get_status())
			set_status(run_process(&ctx));
		add_history(cmd);
		free_cmd(cmd);
	}
	xfree_all();
	return (0);
}
