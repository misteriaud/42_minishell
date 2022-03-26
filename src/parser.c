/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/26 12:09:33 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

enum char_cat get_cat(char c)
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

enum lexer_state get_state(enum lexer_state state, enum char_cat cat)
{
	if (cat == WHITESPACE && state != IN_WORD)
		return (state);
	if (state == START && cat < 8)
		return (cat);
	if (state == MAIN)
	{
		if (cat != SINGLE && cat != DOUBLE) // si autre chose que quote
			return (cat);
	}
	if (state & IN_WORD)
	{
		if (!cat) // si whitespace
			return (MAIN); // on retourne dans le main
		if (cat == GENERAL)
			return (IN_WORD);
	}
	if (state & (IN_SINGLE_QUOTE | IN_DOUBLE_QUOTE)) //in quotes
	{
		if (cat & state) //si fermeture de quote
			return (MAIN);
		return (state);
	}
	if (cat == (PIPE | L_CHEVRON | R_CHEVRON))
		return (state + cat);
	return (ERROR);
}

t_token	*generate_token(t_token *curr_token, enum lexer_state prev_state, char *str)
{
	enum lexer_state	next_state;
	enum char_cat		cat;

	cat = get_cat(*str);
	if (cat == EOF)
		return (curr_token);
	next_state = get_state(prev_state, cat);

}

int parse(t_token **first, char *str)
{
	enum lexer_state	state;
	int					i;
	t_token				*dest;

	if (xmalloc(&dest, sizeof(*dest), PARSING_ALLOC))
		return (ERR_ALLOC_FAILED);
	dest = generate_token(dest, START, str);
}
