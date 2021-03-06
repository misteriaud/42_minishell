/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:33:18 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 16:37:38 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <memory.h>

#define RED_COLOR		"\x1b[3;1;31m"
#define GREEN_COLOR		"\x1b[3;1;32m"
#define PURPLE_COLOR	"\x1b[3;1;33m"
#define YELLOW_COLOR	"\x1b[3;1;35m"

t_err	get_prompt(char **prompt, const unsigned int old_status)
{
	static char		*color[2] = {GREEN_COLOR, RED_COLOR};
	const int		c = !!(old_status);
	char			*pwd;
	char			*join_1;
	char			*join_2;

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
