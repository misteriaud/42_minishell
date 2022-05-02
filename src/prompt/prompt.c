/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:33:18 by artblin           #+#    #+#             */
/*   Updated: 2022/05/02 14:56:52 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>

#include <stdio.h>
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

char	*ft_strnstr(const char *a, const char *b, int x)
{
	int	z;
	int	i;
	int	y;

	i = 0;
	if (!*b)
		return ((char *)a);
	while (*a && i <= x)
	{
		y = 0;
		z = 0;
		while (*(a + z) && b[z] && *(a + z) == b[z])
		{
			z++;
			y++;
		}
		if (b[z] == '\0' && (i + y) <= x)
			return ((char *)a);
		a++;
		i++;
	}
	return ((void *)0);
}

t_err get_prompt(t_ctx *ctx, char **prompt)
{
	//static char		*color[4] = {RED_COLOR, GREEN_COLOR, PURPLE_COLOR, YELLOW_COLOR};
	//static int		c = 0;
	(void)ctx;
	t_str	home;
	char	*current;
	char	*relative;
	int		len;

	current = getcwd(NULL, 0);
	if (!get_variable(ctx, "HOME", &home))
	{
		len = get_len(home.str);
		printf("home --> %s\n", home.str);
		relative = ft_strnstr(current, home.str, len);
		*prompt = relative + len;
		printf("prompt --> %s\n", *prompt);
		return (NO_ERROR);
	}
	*prompt = current;
	return (NO_ERROR);
}
















