/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:35:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 00:52:41 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_cat(char c)
{
	if (!c)
		return (EOF);
	if (c == ' ')
		return (WHITESPACE);
	if (c == '|')
		return (PIPE);
	if (c == '\'')
		return (SINGLE);
	if (c == '"')
		return (DOUBLE);
	if (c == '<')
		return (L_CHEVRON);
	if (c == '>')
		return (R_CHEVRON);
	if (c == '$')
		return (VAR_CHAR);
	return (GENERAL);
}

static inline int	get_state_when_whitespace(int state)
{
	if (state & CHEV_WAIT)
		return (state ^ CHEV_WAIT);
	if (state & AFTER_TOKEN)
		return (AFTER_TOKEN);
	return (state);
}

static inline int	get_state_in_word(t_char_cat cat)
{
	if (!cat)
		return (AFTER_TOKEN);
	if (cat & (L_CHEVRON | R_CHEVRON))
		return (cat + CHEV_WAIT);
	return (IN_WORD);
}

static inline int	get_state_after_cmd(t_char_cat cat)
{
	if (cat & (L_CHEVRON | R_CHEVRON))
		return (cat + CHEV_WAIT);
	return (cat);
}

int	get_state(int state, t_char_cat cat)
{
	if (cat == EOF && state & 766)
		return (ERROR);
	if (cat == EOF)
		return (END);
	if (cat & DOLLAR && (state > 4 || !state))
		return (VAR_CHAR);
	if (cat == WHITESPACE && state != IN_WORD)
	// if (cat == WHITESPACE && state != IN_WORD && (state & (IN_SQ | IN_DQ)) == 0)
		return (get_state_when_whitespace(state));
	if ((state == MAIN && cat < 8) || state & AFTER_TOKEN)
		return (get_state_after_cmd(cat));
	if (state & 248 && cat < 8)
		return (cat);
	if (state & (IN_WORD | VAR_CHAR))
		return (get_state_in_word(cat));
	if (state & (IN_SQ | IN_DQ))
	{
		if (cat & state)
			return (AFTER_TOKEN | cat);
		return (state);
	}
	if (state & CHEV_WAIT && cat & (L_CHEVRON | R_CHEVRON))
		return ((state << 1) + cat);
	return (ERROR);
}
