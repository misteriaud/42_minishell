/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/26 14:25:39 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_cat(char c)
{
	if (!c)
		return EOF;
	if (c == ' ')
		return WHITESPACE;
	if (c == '|')
		return PIPE;
	if (c == '\'')
		return SINGLE;
	if (c == '"')
		return DOUBLE;
	if (c == '<')
		return L_CHEVRON;
	if (c == '>')
		return R_CHEVRON;
	return GENERAL;
}

int get_state(int state, enum char_cat cat)
{
	if (cat == WHITESPACE && state != IN_WORD)
	{
		if (state & CHEVRON_WAITING)
			return (state ^ CHEVRON_WAITING);
		return (state);
	}
	if ((state == MAIN && cat < 8) || state == AFTER_TOKEN)
	{
		if (cat & (L_CHEVRON | R_CHEVRON))
			return (cat + CHEVRON_WAITING);
		return (cat);
	}
	if (state & (AFTER_PIPE | AFTER_L_CHEVRON | AFTER_2L_CHEVRON | AFTER_R_CHEVRON | AFTER_2R_CHEVRON) && cat < 8)
			return (cat);
	if (state & IN_WORD)
	{
		if (!cat) // si whitespace
			return (AFTER_TOKEN); // on retourne dans le main
		if (cat & (L_CHEVRON | R_CHEVRON))
			return (cat + CHEVRON_WAITING);
		return (cat);
	}
	if (state & (IN_SINGLE_QUOTE | IN_DOUBLE_QUOTE)) //in quotes
	{
		if (cat & state) //si fermeture de quote
			return (AFTER_TOKEN);
		return (state);
	}
	if (state & CHEVRON_WAITING && cat & (L_CHEVRON | R_CHEVRON))
		return ((state << 1) + cat);
	return (ERROR);
}

t_token	*generate_token(t_token *curr_token, int prev_state, char *str)
{
	int	state;
	int	cat;

	cat = get_cat(*str);
	if (cat == EOF)
		return (curr_token);
	state = get_state(prev_state, cat);
	if (state > 1 && state % 2)
	{
		printf("ERROR, char %c, state: %d, cat: %d\n", *str, state, cat);
		return (NULL);
	}
	printf("char %c, state: %d, cat: %d\n", *str, state, cat);
	return (generate_token(curr_token, state, str + 1));
}

int parse(t_token **first, char *str)
{
	t_token				*dest;

	(void)first;
	if (xmalloc(&dest, sizeof(*dest), PARSING_ALLOC))
		return (ERR_ALLOC_FAILED);
	dest = generate_token(dest, MAIN, str);
	return (1);
}
