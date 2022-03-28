/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/28 15:07:26 by mriaud           ###   ########.fr       */
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
	if (state == IN_DQ)
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
	else if ((prev_state & A_PIP) && state < 8
		&& new_branch(&token, prev_state, state, CMD))
		return (MEMORY_ERROR);
	else if (prev_state & (A_L_CHEV | A_R_CHEV) && state < 8
		&& new_branch(&token, prev_state, state, PATH))
		return (MEMORY_ERROR);
	else if (prev_state & AFTER_TOKEN && state < 8
		&& new_branch(&token, prev_state, state, ARG))
		return (MEMORY_ERROR);
	if (state == 1 || (prev_state & (IN_WORD | IN_SQ | IN_DQ) && state < 8))
	{
		if (xrealloc(&token->value.str, (token->value.len++) + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		token->value.str[token->value.len - 1] = *str;
	}
	// printf("%s(type %d) from %s\n", token->value.str, token->type, token->prev->value.str);
	return (generate_token(token, state, str + 1));
}

t_err	parse(t_token **first, char *str)
{
	if (xmalloc(first, sizeof(**first), PARS_ALLOC))
		return (MEMORY_ERROR);
	(*first)->type = CMD;
	return (generate_token(*first, MAIN, str));
}
