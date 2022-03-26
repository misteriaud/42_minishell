/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/27 00:30:50 by mriaud           ###   ########.fr       */
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
	return (GENERAL);
}

int	get_state(int state, enum char_cat cat)
{
	if (cat == EOF && state & 766)
		return (ERROR);
	if (cat == EOF)
		return (END);
	if (cat == WHITESPACE && state != IN_WORD)
	{
		if (state & CHEV_WAIT)
			return (state ^ CHEV_WAIT);
		return (state);
	}
	if ((state == MAIN && cat < 8) || state == AFTER_TOKEN)
	{
		if (cat & (L_CHEVRON | R_CHEVRON))
			return (cat + CHEV_WAIT);
		return (cat);
	}
	if (state & 248 && cat < 8)
		return (cat);
	if (state & IN_WORD)
	{
		if (!cat)
			return (AFTER_TOKEN);
		if (cat & (L_CHEVRON | R_CHEVRON))
			return (cat + CHEV_WAIT);
		return (cat);
	}
	if (state & (IN_SQ | IN_DQ))
	{
		if (cat & state)
			return (AFTER_TOKEN);
		return (state);
	}
	if (state & CHEV_WAIT && cat & (L_CHEVRON | R_CHEVRON))
		return ((state << 1) + cat);
	return (ERROR);
}

t_token	*add_token_back(t_token *parent, t_token **first)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*dest;

	prev = NULL;
	curr = *first;
	if (xmalloc(&dest, sizeof(*dest), PARSING_ALLOC))
		return (0);
	dest->prev = parent;
	while (curr && curr->next)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*first = dest;
	else
		curr->next = dest;
	return (dest);
}

int	new_branch(t_token **curr_token, int prev_state, int state, enum token_type type, char c)
{
	while (prev_state && (*curr_token)->type != CMD)
		*curr_token = (*curr_token)->prev;
	if (prev_state == MAIN || prev_state & (A_PIP | A_R_CHEV))
		*curr_token = add_token_back(*curr_token, &(*curr_token)->stdout);
	else if (prev_state & A_L_CHEV)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->stdin);
	else if (prev_state & AFTER_TOKEN && (*curr_token)->type == ARG)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->next);
	else
		*curr_token = add_token_back(*curr_token, &(*curr_token)->arg);
	if (!curr_token)
		return (ERR_ADD_TOKEN);
	(*curr_token)->type = type;
	if ((prev_state & 255) == A_2L_CHEV || (prev_state & 255) == A_2R_CHEV)
		(*curr_token)->type += 4 + ((prev_state & 255) == A_2L_CHEV) * 24;
	if (state == IN_DQ)
		(*curr_token)->type += 1;
	if (state == 1)
	{
		if (xrealloc(&(*curr_token)->value.str,
				((*curr_token)->value.len++) + 1, PARSING_ALLOC))
			return (ERR_ALLOC_FAILED);
		(*curr_token)->value.str[(*curr_token)->value.len - 1] = c;
	}
	return (0);
}

int	generate_token(t_token *curr_token, int prev_state, char *str)
{
	int	state;
	int	cat;

	cat = get_cat(*str);
	state = get_state(prev_state, cat);
	if (state > 1 && state % 2)
		return (1);
	if (!*str)
		return (0);
	else if (((prev_state == MAIN) || prev_state & A_PIP) && state < 8
		&& new_branch(&curr_token, prev_state, state, CMD, *str))
		return (ERR_ADD_TOKEN);
	else if (prev_state & (A_L_CHEV | A_R_CHEV) && state < 8
		&& new_branch(&curr_token, prev_state, state, PATH, *str))
		return (ERR_ADD_TOKEN);
	else if (prev_state & AFTER_TOKEN && state < 8
		&& new_branch(&curr_token, prev_state, state, ARG, *str))
		return (ERR_ADD_TOKEN);
	else if (prev_state & (IN_WORD | IN_SQ | IN_DQ) && state < 8)
	{
		if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
			return (ERR_ALLOC_FAILED);
		curr_token->value.str[curr_token->value.len - 1] = *str;
	}
	return (generate_token(curr_token, state, str + 1));
}

int	parse(t_token **first, char *str)
{
	t_token				*dest;

	(void)first;
	if (xmalloc(&dest, sizeof(*dest), PARSING_ALLOC))
		return (ERR_ALLOC_FAILED);
	if (generate_token(dest, MAIN, str))
		printf("PAS BON\n");
	return (1);
}
