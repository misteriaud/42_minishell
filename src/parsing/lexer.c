/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:35:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/12 12:31:23 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_cat(char **str)
{
	int	result;

	if (!**str)
		return (EOF);
	if (**str == ' ')
		return (WHITESPACE);
	if (**str == '\'')
		return (SINGLE);
	if (**str == '"')
		return (DOUBLE);
	if (**str == '(')
		return (L_PARENT);
	if (**str == ')')
		return (R_PARENT);
	if (**str == '<' || **str == '>')
	{
		result = L_CHEVRON;
		if (**str == '>')
			result = R_CHEVRON;
		if (**str == *(*str + 1))
		{
			*str += 1;
			result += (result << 1);
		}
		return (result);
	}
	if (**str == '&' || **str == '|')
	{
		result = GENERAL;
		if (**str == '|')
			result = PIPE;
		if (**str == *(*str + 1))
		{
			*str += 1;
			result += (result << 1);
		}
		return (result);
	}
	return (GENERAL);
}

static inline t_lexer_state	get_state_when_whitespace(int state)
{
	if (state & AFTER_TOKEN)
		return (AFTER_TOKEN);
	return (state);
}

static inline t_lexer_state	get_state_in_word(t_char_cat cat)
{
	if (cat == WHITESPACE)
		return (AFTER_TOKEN);
	return ((t_lexer_state)cat);
}

static inline t_lexer_state	get_state_after_chev(t_lexer_state state,
	t_char_cat cat)
{
	if (state == MAIN || state & (A_PIP | AFTER_TOKEN | IN_WORD))
		return ((t_lexer_state)cat);
	return (ERROR);
}

t_lexer_state	get_state(t_lexer_state state, t_char_cat cat)
{
	if (cat == EOF && !(state & AFTER_TOKEN) && state & 766)
		return (ERROR);
	if (cat == EOF)
		return (END);
	if (cat == WHITESPACE && state != IN_WORD)
		return (get_state_when_whitespace(state));
	if ((state == MAIN && cat < 8) || state & AFTER_TOKEN || cat > 192)
		return ((t_lexer_state)cat);
	if (state & (IN_SQ | IN_DQ))
	{
		if (cat & state)
			return (AFTER_TOKEN | cat);
		return (state);
	}
	if (cat & (L_CHEVRON | R_CHEVRON | DL_CHEVRON | DR_CHEVRON))
		return (get_state_after_chev(state, cat));
	if (state & 248 && cat < 8)
		return ((t_lexer_state)cat);
	if (state & IN_WORD)
		return (get_state_in_word(cat));
	return (ERROR);
}
