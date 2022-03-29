/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 11:44:53 by mriaud           ###   ########.fr       */
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

static inline void	move_forward(int *prev_state, int *state, char **str)
{
		*str = *str + 1;
		*prev_state = *state;
		*state = get_state(*prev_state, get_cat(**str));
}

static t_err	feed_token(t_token *token, int *prev_state, int *state, char **str)
{
	t_str tmp;

	tmp.len = 0;
	tmp.str = NULL;
	while ((*state > 0 && *state & (IN_WORD | VAR_CHAR)) || (*state == *prev_state && *state < 8 && *state))
	{
		if (xrealloc(&tmp.str, (tmp.len++) + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		tmp.str[tmp.len - 1] = **str;
		move_forward(prev_state, state, str);
	}
	if (tmp.len)
	{
		if (!token->value.str)
			token->value = tmp;
		else if (merge(&token->value, &token->value, &tmp, 0))
			return (MEMORY_ERROR);
	}
	else
		move_forward(prev_state, state, str);
	return (NO_ERROR);
}

static t_err	generate_token(t_token *token, int prev_state, int state, char *str)
{
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
	if (feed_token(token, &prev_state, &state, &str))
		return (MEMORY_ERROR);
	printf("\'%c\'(prev_state: %d, state:%d) %s(type %d)\n", *str, prev_state, state, token->value.str, token->type);
	return (generate_token(token, prev_state, state, str));
}

t_err	parse(t_token **first, char *str)
{
	int	state;

	if (xmalloc(first, sizeof(**first), PARS_ALLOC))
		return (MEMORY_ERROR);
	(*first)->type = CMD;
	state = get_state(MAIN, get_cat(*str));
	return (generate_token(*first, MAIN, state, str));
}
