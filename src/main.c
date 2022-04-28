/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:02:17 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/27 19:38:15 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>

#define RED_COLOR		"\x1b[1;31m"
#define GREEN_COLOR		"\x1b[1;32m"
#define PURPLE_COLOR	"\x1b[1;33m"
#define YELLOW_COLOR	"\x1b[1;35m"
#define RESET_COLOR		"\x1b[0m"
#define MINISHELL		"minishell "
#define ARROW			" > "

#define PROMPT_ABSOLUTE "\x1b[1;31mminishell \x1b[0m"
#define PROMPT_TILDE "\x1b[1;31mminishell ~\x1b[0m"
#define PROMPT_END "\x1b[1;31m > \x1b[0m"

t_err get_prompt(t_ctx *ctx, char **data)
{
	static char		*color[4] = {RED_COLOR, GREEN_COLOR, PURPLE_COLOR, YELLOW_COLOR};
	static int		c = 0;

	char	*join_1;
	char	*join_2;

	t_str	pwd;
	t_str	home;
	int		is_tilde;

	get_variable(ctx, "PWD", &pwd);
	get_variable(ctx, "HOME", &home);
	is_tilde = 0;
	while (pwd.str[is_tilde] == home.str[is_tilde])
		is_tilde++;


	join_1 = str_join(color[c], MINISHELL);
	if (is_tilde)
	{
		join_2 = str_join(join_1, "~");
		xfree(join_1, TMP_ALLOC);
	}
	join_1 = str_join(join_2, RESET_COLOR);
	xfree(join_2, TMP_ALLOC);
	join_2 = str_join(join_1, &pwd.str[is_tilde]);
	xfree(join_1, TMP_ALLOC);
	join_1 = str_join(join_2, color[c]);
	xfree(join_2, TMP_ALLOC);
	join_2 = str_join(join_1, ARROW);
	xfree(join_1, TMP_ALLOC);
	join_1 = str_join(join_2, RESET_COLOR);
	xfree(join_2, TMP_ALLOC);

	*data = join_1;
	c++;
	if (c == 4)
		c = 0;
	return (NO_ERROR);
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
	init_term(&ctx);
	init_env(&ctx, env);
	// init_history(&ctx);
	init_built_in(&ctx);

	char *prompt;
	while (1)
	{
		//cmd = readline("\x1b[0m\x1b[1;31mminishell \x1b[0m> ");
		get_prompt(&ctx, &prompt);
		cmd = readline(prompt);
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
	// printf("\n end of process(%x)\n", err);
	return (0);
}
