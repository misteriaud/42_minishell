/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:35:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/02 11:02:42 by mriaud           ###   ########.fr       */
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
	if (**str == '|')
		return (PIPE);
	if (**str == '\'')
		return (SINGLE);
	if (**str == '"')
		return (DOUBLE);
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
	return (GENERAL);
}

static inline t_lexer_state	get_state_when_whitespace(int state)
{
	// if (state & CHEV_WAIT)
	// 	return (state ^ CHEV_WAIT);
	if (state & AFTER_TOKEN)
		return (AFTER_TOKEN);
	return (state);
}

static inline t_lexer_state	get_state_in_word(t_char_cat cat)
{
	if (!cat)
		return (AFTER_TOKEN);
	// if (cat & (L_CHEVRON | R_CHEVRON))
	// 	return (cat + CHEV_WAIT);
	return ((t_lexer_state)cat);
}

static inline t_lexer_state	get_state_after_cmd(t_char_cat cat)
{
	// if (cat & (L_CHEVRON | R_CHEVRON))
	// 	return (cat + CHEV_WAIT);
	return ((t_lexer_state)cat);
}

static inline t_lexer_state get_state_after_chev(t_lexer_state state, t_char_cat cat)
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
	if ((state == MAIN && cat < 8) || state & AFTER_TOKEN)
		return (get_state_after_cmd(cat));
	if (cat & (L_CHEVRON | R_CHEVRON | DL_CHEVRON | DR_CHEVRON))
		return (get_state_after_chev(state, cat));
	if (state & 248 && cat < 8)
		return ((t_lexer_state)cat);
	if (state & IN_WORD)
		return (get_state_in_word(cat));
	if (state & (IN_SQ | IN_DQ))
	{
		if (cat & state)
			return (AFTER_TOKEN | cat);
		return (state);
	}
	return (ERROR);
}
