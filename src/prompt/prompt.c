/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:33:18 by artblin           #+#    #+#             */
/*   Updated: 2022/05/06 14:09:13 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <memory.h>

#define RED_COLOR		"\x1b[3;1;31m"
#define GREEN_COLOR		"\x1b[3;1;32m"
#define PURPLE_COLOR	"\x1b[3;1;33m"
#define YELLOW_COLOR	"\x1b[3;1;35m"

#include <stdio.h>

t_err get_prompt(t_ctx *ctx, char **prompt)
{
	static char		*color[4] = {GREEN_COLOR, RED_COLOR, PURPLE_COLOR, YELLOW_COLOR};
	const int		c = !!(ctx->status);
	char	*pwd;
	char	*join_1;
	char	*join_2;

	pwd = getcwd(NULL, 0);
	join_1 = str_join(color[c], "minishell\x1b[0m ", PROMPT_ALLOC);
	join_2 = str_join(join_1, pwd, PROMPT_ALLOC);
	xfree(join_1, ENV_ALLOC);
	join_1 = str_join(join_2, color[c], PROMPT_ALLOC);
	xfree(join_2, ENV_ALLOC);
	join_2 = str_join(join_1, " > \x1b[0m", PROMPT_ALLOC);
	xfree(join_1, ENV_ALLOC);
	*prompt = join_2;
	free(pwd);
	return (NO_ERROR);
}
















