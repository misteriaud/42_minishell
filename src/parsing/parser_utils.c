/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:15:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/02 09:52:21 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

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
	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*first = dest;
	else
		prev->next = dest;
	return (dest);
}

t_err	new_branch(t_token **curr_token, t_state state, t_token_type type)
{
	while (state.prev && (*curr_token)->type != CMD)
		*curr_token = (*curr_token)->prev;
	if (state.prev & (AFTER_TOKEN | A_PIP) && !(*curr_token)->value.str)
		return (NO_ERROR);
	if (state.prev == MAIN || state.prev & A_PIP)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->out);
	else if (state.prev & A_L_CHEV)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->in);
	else if (state.prev & A_R_CHEV)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->redir);
	else
		*curr_token = add_token_back(*curr_token, &(*curr_token)->arg);
	if (!curr_token)
		return (MEMORY_ERROR);
	(*curr_token)->type = type;
	if ((state.prev & 255) == A_2L_CHEV || (state.prev & 255) == A_2R_CHEV)
		(*curr_token)->type += 4 + ((state.prev & 255) == A_2L_CHEV) * 24;
	return (NO_ERROR);
}

void	move_forward(t_state *state, char **str)
{
	*str = *str + 1;
	state->prev = state->curr;
	state->curr = get_state(state->prev, get_cat(str));
}

t_err	concat_token(t_ctx *ctx, t_token *token, t_state *state, t_str tmp)
{
	t_str	dest;

	dest = (t_str){NULL, 0};
	if (!(state->prev & IN_SQ) && drop_variables(ctx, &tmp))
		return (MEMORY_ERROR);
	if (!token->value.str)
		token->value = tmp;
	else if (new_str(&dest, tmp.len + token->value.len, PARS_ALLOC)
		|| merge(&dest, &token->value, &tmp, 0))
		return (MEMORY_ERROR);
	if (dest.len)
	{
		xfree(token->value.str, PARS_ALLOC);
		token->value = dest;
	}
	return (NO_ERROR);
}
