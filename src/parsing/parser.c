/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 00:57:33 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*add_token_back(t_token *parent, t_token **first)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*dest;

	prev = NULL;
	curr = *first;
	if (xmalloc(&dest, sizeof(*dest), PARS_ALLOC))
		return (NULL);
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

static t_err	new_branch(t_token **curr_token, int prev_state,
	int state, t_token_type type)
{
	while (prev_state && (*curr_token)->type != CMD)
		*curr_token = (*curr_token)->prev;
	if (prev_state == MAIN || prev_state & (A_PIP | A_R_CHEV))
		*curr_token = add_token_back(*curr_token, &(*curr_token)->out);
	else if (prev_state & A_L_CHEV)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->in);
	else if (prev_state & AFTER_TOKEN && (*curr_token)->type == ARG)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->next);
	else
		*curr_token = add_token_back(*curr_token, &(*curr_token)->arg);
	if (!curr_token)
		return (MEMORY_ERROR);
	(*curr_token)->type = type;
	if ((prev_state & 255) == A_2L_CHEV || (prev_state & 255) == A_2R_CHEV)
		(*curr_token)->type += 4 + ((prev_state & 255) == A_2L_CHEV) * 24;
	if (state & (IN_DQ | DOLLAR))
		(*curr_token)->type += 1;
	return (NO_ERROR);
}

static t_err	generate_token(t_token *token, int prev_state, char *str)
{
	int	state;
	int	cat;

	cat = get_cat(*str);
	state = get_state(prev_state, cat);
	if (state > 1 && state % 2)
		return (LEXING_ERROR);
	if (!*str)
		return (NO_ERROR);
	else if ((prev_state & A_PIP) && (state & 0x3FF) < 8
		&& new_branch(&token, prev_state, state, CMD))
		return (MEMORY_ERROR);
	else if (prev_state & (A_L_CHEV | A_R_CHEV) && (state & 0x3FF) < 8
		&& new_branch(&token, prev_state, state, PATH))
		return (MEMORY_ERROR);
	else if (prev_state == AFTER_TOKEN && (state & 0x3FF) < 8
		&& new_branch(&token, prev_state, state, ARG))
		return (MEMORY_ERROR);
	else if ((prev_state == IN_WORD && state & (IN_SQ | IN_DQ))
			|| ((prev_state & 0x3FF) > AFTER_TOKEN && state < 8 && state != prev_state)
			|| ((prev_state + state) == (IN_DQ & IN_SQ)))
	{
		token = add_token_back(token, &token->next);
		if (!token)
			return (MEMORY_ERROR);
		token->type = FOLLOW;
		if (state == IN_DQ)
			token->type += 1;
	}
	if (state == IN_WORD || (state == prev_state && state < 8))
	{
		if (xrealloc(&token->value.str, (token->value.len++) + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		token->value.str[token->value.len - 1] = *str;
	}
	printf("\'%c\'(prev_state: %d, state:%d) %s(type %d)\n", *str, prev_state, state, token->value.str, token->type);
	return (generate_token(token, state, str + 1));
}

t_err	parse(t_token **first, char *str)
{
	if (xmalloc(first, sizeof(**first), PARS_ALLOC))
		return (MEMORY_ERROR);
	(*first)->type = CMD;
	return (generate_token(*first, MAIN, str));
}
